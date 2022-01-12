#ifndef PULSAR_CONSUMER_H
#define PULSAR_CONSUMER_H

#include "pulsar/Client.h"
#include "pulsar/Consumer.h"
#include "pulsar/ConsumerConfiguration.h"
#include "pulsar/Message.h"
#include "pulsar/Result.h"
#include "pulsar/ConsumerType.h"
#include "pulsar/KeySharedPolicy.h"


using namespace pulsar;
using std::string;

namespace message_pulsar
{
class Pulsar_Consumer {
  private:
    string brokers_list; // IP addresses of pulsar brokers, format: pulsar:://<pulsar_host_ip>:<port>, example: pulsar://10.213.43.188:9092

    string subscription_name; // Subscription name of the pulsar consumer

    string topic_name; //A string representation of the topic to be consumed, for example: /hostid/00000000-0000-0000-0000-000000000000/netwconf/

    ConsumerConfiguration consumer_config; //Configuration of the pulsar consumer

    Client *ptr_client; //A pointer to the pulsar client

    Consumer consumer;

  private:
    void setSubscriptionName(string subscription_name);

    void setBrokers(string brokers);

    void setTopicName(string topic);

    
  public:
    Pulsar_Consumer(string topic, string brokers, string subscription_name);

    ~Pulsar_Consumer();

    string getBrokers() const;

    string getTopicName() const;

    string getSubscriptionName() const;

    bool ConsumerDispatched();

    //static void listener(Consumer consumer, const Message& message);

  
};

} // namespace message_pulsar
#endif