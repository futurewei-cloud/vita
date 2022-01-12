#ifndef PULSAR_PRODUCER_H
#define PULSAR_PRODUCER_H

#include "pulsar/Client.h"
#include "pulsar/Producer.h"
#include "pulsar/ProducerConfiguration.h"
#include "pulsar/Message.h"
#include "pulsar/MessageBuilder.h"
#include "pulsar/Result.h"

using namespace std;
using namespace pulsar;

namespace amessage_pulsar
{
class Pulsar_Producer {
  private:
  string brokers_list; //IP addresses of Pulsar brokers, format: pulsar://<pulsar_host_ip>:<port>, example:pulsar://10.213.43.188:9092

  string topic_name; //A string representation of the topic name to be published, example: /hostid/00000000-0000-0000-0000-000000000000/netwconf/

  ClientConfiguration client_config; //Configuration of the pulsar client

  Client *ptr_client; //A pointer to the pulsar client

  public:
  Pulsar_Producer(string brokers, string topic);

  ~Pulsar_Producer();

  string getBrokers() const;

  string getTopicName() const;

  void setTopicName(string topic);

  bool publish(string message);

  bool publish(string message, string key);


  private:
  void setBrokers(string brokers);

};

} // _message_pulsar

#endif