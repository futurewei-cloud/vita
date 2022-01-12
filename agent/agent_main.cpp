#include "pulsar_consumer.h"
#include "kafka_consumer.h"
#include <thread>
#include <chrono>
#include <unistd.h> /* for getopt */

using message_pulsar::Pulsar_Consumer;
using message_kafka::Kafka_Consumer;
using std::string;
using namespace std;

static char PULSAR_BROKER_LIST[] = "pulsar://localhost:6650";
static char KAFKA_BROKER_LIST[] = "localhost:9092"
static char TOPIC[] = "Host-ts-1";
static char SUBSCRIPTION_NAME[] = "Test-Subscription";
static char GROUP_ID[] = "Test_Group";

string g_pulsar_broker_list = EMPTY_STRING;
string g_kafka_broker_list = EMPTY_STRING;
string g_topic = EMPTY_STRING;
string g_subsription_name = EMPTY_STRING;
string g_group_id = EMPTY_STRING;

int main(int argc, char *argv[])
{
  int option;
  int rc = 0;

  printf("%s", "Control Agent started...\n");

  while ((option = getopt(argc, argv, "p:k:h:s:g")) != -1) {
    switch (option) {
    case 'p':
      g_pulsar_broker_list = optarg;
      break;
    case 'k':
      g_kafka_broker_list = optarg;
      break;
    case 'h':
      g_topic = optarg;
      break;
    case 's':
      g_subsription_name = optarg;
      break;
    case 'g':
      g_group_id = optarg;
      break;
    default: //the '?' case when the option is not recognized
      fprintf(stderr,
              "Usage: %s\n"
              "\t\t[-p puslar broker list]\n"
              "\t\t[-k kafka broker list]\n"
              "\t\t[-h host topic to listen]\n"
              "\t\t[-s subscription name]\n"
              "\t\t[-g group id]\n",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  // fill in the information if not provided in command line args
  if (g_pulsar_broker_list == EMPTY_STRING) {
    g_pulsar_broker_list = BROKER_LIST;
  }

  if (g_kafka_broker_list == EMPTY_STRING) {
    g_kafka_broker_list = BROKER_LIST;
  }
  if (g_topic == EMPTY_STRING) {
    g_topic = TOPIC;
  }
  if (g_subsription_name == EMPTY_STRING) {
    g_subsription_name = PSUBSCRIPTION_NAME;
  }

  Pulsar_Consumer pulsar_consumer(g_topic, g_broker_list, g_subsription_name);
  pulsar_consumer.unicastConsumerDispatched();

  Kafka_Consumer kafka_consumer(g_topic, g_broker_list, g_subsription_name);
  pulsar_consumer.unicastConsumerDispatched();

  pause();

  return 0;

}