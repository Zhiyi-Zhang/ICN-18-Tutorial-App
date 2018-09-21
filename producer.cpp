#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/signing-helpers.hpp>

#include <iostream>

namespace ndn {
namespace examples {

class Producer : noncopyable
{
public:
  Producer()
  {
    counter = 0;
  }

  void
  run()
  {
    m_face.setInterestFilter("/home/LivingRoom/Camera-01",
                             bind(&Producer::onInterest, this, _1, _2),
                             RegisterPrefixSuccessCallback(),
                             bind(&Producer::onRegisterFailed, this, _1, _2));
    m_face.processEvents();
  }

private:
  void
  onInterest(const InterestFilter& filter, const Interest& interest)
  {
    std::cout << "<< I: " << interest << std::endl;

    Name dataName(interest.getName());
    dataName
      .appendVersion();  // add "version" component (current UNIX timestamp in milliseconds)

    static const std::string content = "HELLO ICN 2018";

    // Create Data packet
    shared_ptr<Data> data = make_shared<Data>();
    data->setName(dataName);
    data->setFreshnessPeriod(2_s);
    data->setContent(reinterpret_cast<const uint8_t*>(content.data()), content.size());

    // Sign Data packet with default identity
    // m_keyChain.sign(*data);

    // const auto& pib = m_keyChain.getPib();
    // auto identity = pib.getIdentity(entry.m_caName);
    // auto cert = identity.getDefaultKey().getDefaultCertificate();

    if (counter % 2 == 0) {
      m_keyChain.sign(*data, signingByIdentity(Name("/home/LivingRoom/Camera-01")));
      counter++;
    }
    else {
      m_keyChain.sign(*data, signingByIdentity(Name("/ndn/edu/ucla/alice")));
      counter++;
    }

    // m_keyChain.sign(*data, signingByIdentity(identity));
    // m_keyChain.sign(*data, signingByKey(identity.getDefaultKey()));
    // m_keyChain.sign(*data, signingByCertificate(cert));


    // Return Data packet to the requester
    std::cout << ">> D: " << *data << std::endl;
    m_face.put(*data);
  }


  void
  onRegisterFailed(const Name& prefix, const std::string& reason)
  {
    std::cerr << "ERROR: Failed to register prefix \""
              << prefix << "\" in local hub's daemon (" << reason << ")"
              << std::endl;
    m_face.shutdown();
  }

private:
  Face m_face;
  KeyChain m_keyChain;
  int counter;
};

} // namespace examples
} // namespace ndn

int
main(int argc, char** argv)
{
  ndn::examples::Producer producer;
  try {
    producer.run();
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
  return 0;
}
