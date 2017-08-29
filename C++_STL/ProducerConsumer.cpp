#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
int iCounting = 0;
bool ready = false;
bool processed = false;

using namespace std;

void Producer()
{
    std::cout << "Producer thread is Produding data now"<< endl  ;
    while (1) {
       std::unique_lock<std::mutex> lk(m);

       if ( !processed ){ ready = true; }
       cv.wait(lk, []{return ready;});
       cout << "*******************************************************" << endl;
       cout << "Producer: Received notification from {" << data << "}" << endl;
       data.clear();
       data += "Producer";
       iCounting++;
       cout << "Produced: [" << iCounting << "]" << endl;

       
       if ( ready ){
            ready = false;
            processed = true;
            cout << "Waiting for the Consumer to wakeup!"  <<  endl;
            cout << "*******************************************************" << endl;
            std::this_thread::sleep_for (std::chrono::seconds(1)); 
            lk.unlock();
            cv.notify_all();
        }
    }
    std::cout << "Producer thread signals data processing completed" << endl;
}

void Consumer()
{
    std::cout << "Consumer thread is consuming data" << endl;
    while(1){
        std::unique_lock<std::mutex> lk(m);
        if( !ready ){ processed = true; }

        
        cv.wait(lk, []{return processed;});
        cout << "###########################################################" << endl;
        cout << "Consumer Consuming Provided by :[" << data << "]" <<  endl;
        cout <<  "Consumed: [" << iCounting << "]" << endl;
        data.clear();
        data += "Consumer";
        if ( processed  ){
            ready = true;
            processed = false;

            cout <<  "Waiting for Producer to wakeup and start producing again..." << endl;
            cout << "###########################################################" << endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            lk.unlock();
            cv.notify_all(); 
        }      
    }
    std::cout << "Consumer thread signals data consumption completed" << endl;
}

int main()
{
    std::thread ProducerThread(Producer);
    std::thread ConsumerThread(Consumer);

    ProducerThread.join();
    ConsumerThread.join();

    std::cout << "Back in main(), data = " << data << '\n';
}
