#include "servicemananger.h"


service_manager::service_manager(const std::shared_ptr<settings> &my_settings)
{
    is_started = false;
    m_settings = my_settings;
    threads_to_deleting = 0;
    try {
        int num = m_settings->operator [](std::string("num_treads"));
        set_num_threads(num);
    } catch (EmptyProperty *e) {
        int num = std::thread::hardware_concurrency();
        if (num == 0){
            set_num_threads(4);
        } else {
            set_num_threads(num);
        }
    }
}

service_manager::~service_manager()
{
    shutdown();
}

void service_manager::run_service(const std::shared_ptr<service> &new_service)
{
    services.push_back(new_service);
    if(is_started){
        service_threads.push_back(std::thread(&service::run, services.back()));
    }
}

void service_manager::start()
{
    if (!is_started) {
        for (int i = 0; i < services.size(); i++){
            service_threads.push_back(std::thread(&service::run, services.back()));
        }
        is_started = true;
    }
}

void service_manager::shutdown()
{
    if (is_started) {
        task_threads.resize(0);
        for (int i = 0; i < services.size(); i++) {
            services.at(i)->shutdown();
        }
    }
}

void service_manager::run_task(const std::function<void ()> &task) throw (BusyThreads, NotStarted)
{
    if (is_started) {
        if (task_threads.size() < num_treads) {
            task_threads.push_back(std::thread(task));
        } else {
            bool success = false;
            delete_threads();
            for (int i = 0; i < task_threads.size(); i++) {
                if (!task_threads.at(i).joinable()) {
                    task_threads.at(i) = std::thread(task);
                    success = true;
                }
            }
            if (!success) {
                throw BusyThreads();
            }
        }
    } else {
        throw NotStarted();
    }
}

void service_manager::set_num_threads(size_t count)
{
    num_treads = count;
    if (count < num_treads){
        threads_to_deleting = num_treads - count;
        delete_threads();
    }
    save_config();
}

void service_manager::save_config()
{
    m_settings->operator [](std::string("num_treads")) = num_treads;
}

void service_manager::delete_threads()
{
    for (int i = 0; i < task_threads.size(); i++) {
        if (threads_to_deleting > 0) {
            if (!task_threads.at(i).joinable()){
                task_threads.erase(task_threads.begin() + i);
                i--;
                threads_to_deleting--;
            }
        } else {
            break;
        }
    }
}
