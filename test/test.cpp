#include <assert.h>
#include <iostream>
#include <google/protobuf/message_lite.h>
#include "test.pb.h"

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    {
        // Create message
        Test origin;
        origin.add_test_id(2);
        origin.add_test_id(4);

        std::cout << "Before serialization:" << std::endl;
        for (int i = 0; i < origin.test_id_size(); ++i) {
            std::cout << origin.test_id(i) << std::endl;
        }

        // Serialize message
        std::string serialized;
        assert(origin.SerializeToString(&serialized));

        // Parse serialized string of message
        Test result;
        assert(result.ParseFromString(serialized));

        std::cout << "After parsing:" << std::endl;
        for (int i = 0; i < result.test_id_size(); ++i) {
            std::cout << result.test_id(i) << std::endl;
        }
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
