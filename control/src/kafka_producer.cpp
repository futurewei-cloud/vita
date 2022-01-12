#include <iostream>
#include <stdexcept>
#include "aca_message_producer.h"

using namespace std;
using namespace cppkafka;

namespace message_kafka
{
KafkaProducer::KafkaProducer(string brokers, string topic, int partition)
{
  setBrokers(brokers);
  setTopicName(topic);
  setPartitionValue(partition);

  // Construct the configuration
  this->config = { { "metadata.broker.list", this->brokers_list } };

  // Create the producer
  this->ptr_producer = new Producer(this->config);
}

KafkaProducer::~KafkaProducer()
{
  delete ptr_producer;
}

string KafkaProducer::getBrokers() const
{
  return this->brokers_list;
}

string KafkaProducer::getTopicName() const
{
  return this->topic_name;
}

void KafkaProducer::setTopicName(string topic)
{
  this->topic_name = topic;
}

int KafkaProducer::getPartitionValue() const
{
  return this->partition_value;
}

void KafkaProducer::setPartitionValue(int partition)
{
  if (partition < -1) {
    throw invalid_argument("Negative partition value");
  }

  this->partition_value = partition;
}

void KafkaProducer::publish(string message)
{
  // Create a message builder for this topic
  MessageBuilder builder(this->topic_name);

  // Get the partition. If no partition is provided, this will be an unassigned one
  if (partition_value != -1) {
    builder.partition(this->partition_value);
  }

  // Set the payload on this builder
  builder.payload(message);

  // Actually produce the message
  this->ptr_producer->produce(builder);

  // Flush all produced messages
  this->ptr_producer->flush();
}

void KafkaProducer::setBrokers(string brokers)
{
  //TODO: validate string as IP address
  this->brokers_list = brokers;
}

} // namespace messagemanager