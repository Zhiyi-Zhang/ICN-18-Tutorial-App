#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/validator-config.hpp>
#include <iostream>

namespace ndn {
namespace examples {

class Consumer : noncopyable
{
public:
  Consumer(const std::string& fileName = "rules.conf")
    : m_face()
    , validator(m_face)
  {
    validator.load(fileName);
  }

  void
  run()
  {
    Interest interest(Name("/home/LivingRoom/Camera-01"));
    interest.setInterestLifetime(2_s); // 2 seconds
    interest.setMustBeFresh(true);

    m_face.expressInterest(interest,
                           bind(&Consumer::onData, this,  _1, _2),
                           bind(&Consumer::onNack, this, _1, _2),
                           bind(&Consumer::onTimeout, this, _1));

    std::cout << "Sending " << interest << std::endl;
    m_face.processEvents();
  }

private:
  void
  onData(const Interest& interest, const Data& data)
  {
    std::cout << data << std::endl;
    std::cout << "Key Locator Value: " << data.getSignature().getKeyLocator() << std::endl;
    validator.validate(data,
                       [&] (auto&&...) { std::cout << "Validation Succeed" << std::endl; },
                       [&] (auto&&...) { std::cout << "Validation Failed" << std::endl; });
  }

  void
  onNack(const Interest& interest, const lp::Nack& nack)
  {
    std::cout << "received Nack with reason " << nack.getReason()
              << " for interest " << interest << std::endl;
  }

  void
  onTimeout(const Interest& interest)
  {
    std::cout << "Timeout " << interest << std::endl;
  }

private:
  Face m_face;
  ValidatorConfig validator;
};

} // namespace examples
} // namespace ndn

int
main(int argc, char** argv)
{
  std::string configFile = "rules.conf";
  if (argc == 2) {
    configFile = argv[1];
  }

  ndn::examples::Consumer consumer(configFile);
  try {
    consumer.run();
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
  return 0;
}
