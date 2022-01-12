#include "aca_message_pulsar_consumer.h"

using pulsar::Client;
using pulsar::ConsumerConfiguration;
using pulsar::Consumer;
using pulsar::Message;
using pulsar::Result;
using pulsar::KeySharedPolicy;
using pulsar::StickyRange;


namespace message_pulsar
{

void listener(Consumer consumer, const Message& message){
  int rc;
  Result result;

  printf("\n<=====incoming message: %s\n",
                message.getDataAsString().c_str());
  
  
  // Now acknowledge message
  consumer.acknowledge(message.getMessageId());
}

Pulsar_Consumer::Pulsar_Consumer(string topic, string brokers, string subscription_name)
{
  setTopicName(topic);
  setBrokers(brokers);
  setSubscriptionName(subscription_name);
  // Create the clients
  //this->ptr_multicast_client= new Client(brokers);
  this->ptr_client = new Client(brokers);
}

Pulsar_Consumer::~Pulsar_Consumer()
{
  delete this->ptr_client;
}

string Pulsar_Consumer::getBrokers() const
{
  return this->brokers_list;
}

string Pulsar_Consumer::getMulticastTopicName() const
{
  return this->topic_name;
}

string Pulsar_Consumer::getMulticastSubscriptionName() const
{
  return this->subscription_name;
}



bool Pulsar_Consumer::ConsumerDispatched(){
  Result result;

  // Use the default exclusive mode
  this->consumer_config.setMessageListener(listener);
  result = this->ptr_client->subscribe(this->topic_name,this->subscription_name,this->consumer_config,this->consumer);
  if (result != Result::ResultOk){
    printf("Failed to subscribe multicast topic: %s\n", this->topic_name.c_str());
    return false;
  }
  return true;
}


void Pulsar_Consumer::setBrokers(string brokers)
{
  this->brokers_list = brokers;
}

void Pulsar_Consumer::setTopicName(string topic)
{
  this->topic_name = topic;
}

void Pulsar_Consumer::setSubscriptionName(string subscription_name)
{
  this->subscription_name = subscription_name;
}


} // namespace message_pulsar