#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    int T; cin >> T;
    cout << setiosflags(ios::uppercase);
    cout << setw(0xf) << internal;
    while (T--) {
        double A; cin >> A;
        double B; cin >> B;
        double C; cin >> C;

        //setw side-effects are local
        //showpos is a global ostream format modifier
        //without rounding up
        
        cout << nouppercase;
        //left and right justify cancels the internal spacing effect
        cout << left;
        //hex only works for integral, or money_type, data type.
        //simply truncating the decimal digits won't show hex. casting is necessary
        //casting a floating point type to an integral type chops the decimals
        //but make sure the byte size matches!
        cout << showbase << hex << static_cast<unsigned long>(A) << ' ';// << endl;
        cout << dec << noshowbase;
        cout << right;
        cout << fixed << setprecision(2) << setw(15) << setfill('_') << showpos << B << noshowpos << ' ';// << endl;
        //In fixed and scientific format, setprecision is the number of digits behind decimal.
        //in general case, setprecision is the number of significat figures!
        cout << scientific << uppercase << setprecision(9) << C << '\r';// endl;
        cout.unsetf(ios::fixed | ios::scientific);

    }
    return 0;

}