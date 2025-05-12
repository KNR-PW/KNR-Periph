#include <map>
#include <functional>

class PeripheralFactory
{
    public:
        using Creator = std::function<IPeripheral*()>;

        static PeripheralFactory& instance() {
            static PeripheralFactory inst;
            return inst;
        }

        void registerCreator(const std::string& name, Creator c)
        {
            creators[name] = c;
        }
     
        IPeripheral* create(const std::string& name) 
        {
            return creators.count(name) ? creators[name]() : nullptr;
        }

    private:
        std::map<std::string, Creator> creators;


}