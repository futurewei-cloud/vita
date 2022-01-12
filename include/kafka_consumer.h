#ifndef KAFKA_CONSUMER_H
#define KAFKA_CONSUMER_H

#include "cppkafka/consumer.h"
#include "cppkafka/configuration.h"

using cppkafka::Configuration;
using cppkafka::Consumer;
using std::string;

namespace message_kafka
{
class KafkaConsumer {
  private:
  string brokers_list; //IP addresses of Kafka brokers, format: <Kafka_host_ip>:<port>, example:10.213.43.188:9092

  string group_id; //Group id of the Kafka consumer

  string topic_name; //A string representation of the topic to be consumed, for example: /hostid/00000000-0000-0000-0000-000000000000/netwconf/

  Configuration config; //Configuration of the Kafka consumer

  Consumer *ptr_consumer; //A pointer to the Kafka consumer

  public:
  KafkaConsumer(string brokers, string group_id);

  ~KafkaConsumer();

  string getBrokers() const;

  string getLastTopicName() const;

  string getGroupId() const;

  void setGroupId(string group_id);

  bool consumeDispatched(string topic);

  private:
  void setBrokers(string brokers);

  void setLastTopicName(string topic);
};

} // namespace messagemanager

#endif