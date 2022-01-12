#include "aca_message_consumer.h"
#include "cppkafka/utils/consumer_dispatcher.h"

extern cppkafka::ConsumerDispatcher *dispatcher;

using cppkafka::Configuration;
using cppkafka::Consumer;
using cppkafka::ConsumerDispatcher;
using cppkafka::Error;
using cppkafka::Message;
using cppkafka::TopicPartition;
using cppkafka::TopicPartitionList;

namespace message_kafka
{
KafkaConsumer::KafkaConsumer(string brokers, string group_id)
{
  setBrokers(brokers);
  setGroupId(group_id);

  // Construct the configuration
  this->config = { { "metadata.broker.list", this->brokers_list },
                   { "group.id", this->group_id },
                   // Disable auto commit
                   { "enable.auto.commit", false },
                   { "auto.offset.reset", "earliest" } };

  ACA_LOG_DEBUG("Broker list: %s\n", this->brokers_list.c_str());
  ACA_LOG_DEBUG("Consumer group.id: %s\n", this->group_id.c_str());

  // Create the consumer
  this->ptr_consumer = new Consumer(this->config);
}

KafkaConsumer::~KafkaConsumer()
{
  delete ptr_consumer;
}

string KafkaConsumer::getBrokers() const
{
  return this->brokers_list;
}

string KafkaConsumer::getLastTopicName() const
{
  return this->topic_name;
}

string KafkaConsumer::getGroupId() const
{
  return this->group_id;
}

void KafkaConsumer::setGroupId(string group_id)
{
  this->group_id = group_id;
}

bool KafkaConsumer::consumeDispatched(string topic)
{
  int rc = true;

  this->ptr_consumer->subscribe({ topic });

  printf("Dispatcher consuming messages from topic: %s\n", topic.c_str());

  // Create a consumer dispatcher
  dispatcher = new ConsumerDispatcher(*(this->ptr_consumer));

  // Now run the dispatcher, providing a callback to handle messages, one to handle
  // errors and another one to handle EOF on a partition
  dispatcher->run(
          // Callback executed whenever a new message is consumed
          [&](Message message) {
            // Print the key (if any)
            if (message.get_key()) {
              printf("%s  -> ", string(message.get_key()).c_str());
            }
            // Print the payload
            printf("\n<=====incoming message: %s\n",
                          string(message.get_payload()).c_str());

            }
            // Now commit the message
            this->ptr_consumer->commit(message);
          },
          // Whenever there's an error (other than the EOF soft error)
          [](Error error) {
            printf("[+] Received error notification: %s\n",
                          error.to_string().c_str());
            rc = false
          },
          // Whenever EOF is reached on a partition, print this
          [](ConsumerDispatcher::EndOfFile, const TopicPartition &topic_partition) {
            printf("Reached EOF on partition: %s\n",
                          topic_partition.get_topic().c_str());
          });

  return rc;
}

void KafkaConsumer::setBrokers(string brokers)
{
  this->brokers_list = brokers;
}

void KafkaConsumer::setLastTopicName(string topic)
{
  this->topic_name = topic;
}

} // namespace message_kafka