#include <iostream>
#include <stdexcept>
#include "pulsar_producer.h"



using namespace std;
using namespace pulsar;

namespace message_pulsar
{
Pulsar_Producer::Pulsar_Producer(string brokers, string topic)
{
  setBrokers(brokers);
  setTopicName(topic);

  // Create client
  this->ptr_client= new Client(brokers,this->client_config);
}

Pulsar_Producer::~Pulsar_Producer()
{
  delete this->ptr_client;
}

string Pulsar_Producer::getBrokers() const
{
  return this->brokers_list;
}

string Pulsar_Producer::getTopicName() const
{
  return this->topic_name;
}

void Pulsar_Producer::setTopicName(string topic)
{
  this->topic_name = topic;
}


bool Pulsar_Producer::publish(string message)
{
  Result result;

  // Create a producer
  Producer producer;
  result = this->ptr_client->createProducer(this->topic_name,producer);
  if(result != ResultOk){
    ACA_LOG_ERROR("Failed to create producer, result=%d.\n", result);
    return EXIT_FAILURE;
  }

  // Create a message
  Message msg = MessageBuilder().setContent(message).build();
  result = producer.send(msg);
  if(result != ResultOk){
    ACA_LOG_ERROR("Failed to send message %s.\n", message.c_str());
    return EXIT_FAILURE;
  }

  ACA_LOG_INFO("Successfully send message %s\n", message.c_str());

  // Flush all produced messages
  producer.flush();
  producer.close();
  return EXIT_SUCCESS;

}

bool Pulsar_Producer::publish(string message, string orderingKey)
{
    Result result;

    // Create a producer
    Producer producer;
    result = this->ptr_client->createProducer(this->topic_name,producer);
    if(result != ResultOk){
        ACA_LOG_ERROR("Failed to create producer, result=%d.\n", result);
        return EXIT_FAILURE;
    }

    // Create a message
    Message msg = MessageBuilder().setContent(message).setOrderingKey(orderingKey).build();
    result = producer.send(msg);
    if(result != ResultOk){
        ACA_LOG_ERROR("Failed to send message %s.\n", message.c_str());
        return EXIT_FAILURE;
    }

    ACA_LOG_INFO("Successfully send message %s\n", message.c_str());

    // Flush all produced messages
    producer.flush();
    producer.close();
    return EXIT_SUCCESS;

}
void Pulsar_Producer::setBrokers(string brokers)
{
  this->brokers_list = brokers;
}

} // namespace message_pulsar