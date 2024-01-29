#include <bits/stdc++.h>
#include <ctime>

#define ll long long int
using namespace std;

void transmission(ll &i, ll &N, ll &tf, ll &tt) {
    while (i <= tf) {
        vector<int> ack(N, 0); // Vector to store acknowledgment status for each frame in the window
        int base = i;          // Base of the sending window

        for (int k = i; k < i + N && k <= tf; k++) {
            cout << "Sending Frame " << k << "..." << endl;
            tt++;
        }

        // Simulating acknowledgments for frames in the window
        for (int k = i; k < i + N && k <= tf; k++) {
            int f = rand() % 2;
            if (!f) {
                cout << "Acknowledgment for Frame " << k << "..." << endl;
                ack[k - base] = 1; // Mark the frame as acknowledged
            } else {
                cout << "Timeout!! Frame Number : " << k << " Not Received" << endl;
            }
        }

        // Check for frames that need retransmission
        for (int k = 0; k < N; k++) {
            if (ack[k] == 0) {
                int frameToResend = base + k;
                cout << "Retransmitting Frame " << frameToResend << "..." << endl;
                tt++;
            }
        }

        cout << "\n";
        i += N;
    }
}

int main() {
    ll tf, N, tt = 0;
    srand(time(NULL));
    cout << "Enter the Total number of frames : ";
    cin >> tf;
    cout << "Enter the Window Size : ";
    cin >> N;
    ll i = 1;
    transmission(i, N, tf, tt);
    cout << "Total number of frames which were sent and resent are : " << tt << endl;
    return 0;
}
