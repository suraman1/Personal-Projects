#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

// Method to determine pager faults using FIFO
int getPageFaults(vector<int> &pages, vector<int> &pageFrames, int frames)
{
    
    // Total number of pages 
    const int n = pages.size();

    // Return if frames is less than or equal to zero
    if (frames <= 0) {
        return n;
    }
    // To denote the current pages, we use an unordered_set
    // And to check the availability of a page

    unordered_set <int> page_set;
    // The code will store the pages in FIFO technique
    queue <int> page_queue;
    
    // Stating from the first page
    int countPageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        // Checking the capacity to hold more pages
        if (page_set.size() < frames)
        {
            // if the page is absent, insert it into the page_set
            // the condition represents page fault

            if (page_set.find(pages[i]) == page_set.end())
            {
                page_set.insert(pages[i]);

                // increment the conter for page fault
                countPageFaults++;
            
                // Push the current page into the queue
                page_queue.push(pages[i]);
            }
        }

        // If the queue is full, we need to remove one page through FIFO
        // The top most page from the queue will be removed
        // Now insert the current page to meet the demand

        else
        {
            // Check if the page in demand is not already present in the queue
            if (page_set.find(pages[i]) == page_set.end())
            {
                // Remove the first page from the queue
                int frontPage = page_queue.front();
                page_queue.pop();
                
                // Erase the index page from the page_set
                page_set.erase(frontPage);
                
                // Push the current page in the page_set and the page_queue
                page_set.insert(pages[i]);
                page_queue.push(pages[i]);
                
                // Increment page faults
                countPageFaults++;
            }
        }
    }
    
    // Adding the current pages to pageFrames

    queue<int> page_frame_queue = page_queue;

    while(!page_frame_queue.empty()) {
        pageFrames.push_back(page_frame_queue.front());
        page_frame_queue.pop();
    }
    return countPageFaults;
}

int main()
{
    vector<int> pages = {4, 1, 2, 4, 5, 3};
    int frames = 4;
    vector<int> pageFrames;

    cout << "Page Faults: " << getPageFaults(pages, pageFrames, frames) << endl;
    cout << "Page Frames After Replacement: ";

    for(auto i : pageFrames) {
        cout << i << " ";
    }
}