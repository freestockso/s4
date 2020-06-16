#include "network/tcp_client.h"

using namespace S4;
using namespace S4::NW;


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: chat_client <port>\n";
      return 1;
    }

    tcp_json_client_t t(argv[1]);
    t.start();

    char line[chat_message::max_body_length + 1];
    while (std::cin.getline(line, chat_message::max_body_length + 1))
    {
      try{
        json_ptr_t j = std::make_shared<json>(json::parse(line));
        t.write(j);
      }catch(std::exception& e){
        std::cerr << "json: Exception: " << e.what() << "\n";
        break;
      }

	  json_ptr_t jr;
	  if (t.read(jr)) {
		  std::cout << "-- read:" << std::endl;
		  std::cout << jr->dump(4) << std::endl;
	  }

    }

    t.stop();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}