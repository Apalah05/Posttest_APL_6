#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

#define MAX 100

struct data2 {
    string nama;
    string jenis;
    string jumlah;
};  

data2 dataATK[MAX];
int pos = 0;

void Tampil() {
    if (pos > 0) {
        cout << "Data ATK/S Ditampilkan\n";
        for (int i = 0; i < pos; i++) {
            cout << i + 1 << ". Nama: " << dataATK[i].nama << ", Jenis: " << dataATK[i].jenis << ", Jumlah: " << dataATK[i].jumlah << endl;
        }
    } else {
        cout << "=== Data Masih Kosong ===\n";
    }
}

void Tambah(data2* data) {
    if (pos >= MAX) {
        cout << "Gudang Data ATK/S Telah Penuh \n";
        return;
    }

        cout << "Tambah Data ATK/S (Nama barang, Jenis barang, dan Jumlah barang) yang di inginkan(dipisahkan dengan koma ','): ";
        string datakan1;
        getline (cin, datakan1);
        size_t nemu = datakan1.find(',');
        if (nemu != string::npos) {
            data[pos].nama = datakan1.substr(0, nemu);
            size_t nemu2 = datakan1.find(',', nemu + 1);
            if (nemu2 != string::npos) {
                data[pos].jenis = datakan1.substr(nemu + 1, nemu2 - nemu - 1);
                data[pos].jumlah = datakan1.substr(nemu2 + 1);
                    pos++;
                } else {
                    cout << "Format Pada Data ATK/S Invalid \n";
                }
            } else {
                cout << "Gudang Data ATK/S Telah Penuh \n";
            } 
            Tampil();
}
        
void Ubah(data2* data) {
    Tampil();
    cout << "Ubah Data Ke: ";
    int y;
    cin >> y;
    if (y > 0 && y <= pos) {
        cin.ignore();
        cout << "Masukkan Data Nama, Jenis, dan Jumlah ATK/S yang Baru(dipisahkan dengan koma','): ";
        string datakan1;
        getline(cin, datakan1);
        size_t nemu = datakan1.find(',');
        if (nemu != string::npos) {
            data[y - 1].nama = datakan1.substr(0, nemu);
            size_t nemu2 = datakan1.find(',', nemu + 1);
            if (nemu2 != string::npos) {
                data[y - 1].jenis = datakan1.substr(nemu + 1, nemu2 - nemu - 1);
                data[y-1].jumlah = datakan1.substr(nemu2 + 1);
            } else {
                cout << "Format Pada Data ATK/S Invalid \n";
                return;
            }
        } else {
            cout << "Format Pada Data ATK/S Invalid \n";
            return;
        }
    } else {
        cout << "Nomor Yang Dimasukkan Pada Data ATK/S Invalid \n";
    }
    Tampil();
}

void Hapus() {
    Tampil();
    cout << "Hapus Data ke: ";
    int x;
    cin >> x;
    if (x > 0 && x <= pos) {
        for (int i = x; i < pos; i++) {
            dataATK[i - 1] = dataATK[i];
        }
        pos--;
    } else {
        cout << "Nomor Yang Dimasukkan Pada Data ATK/S Invalid \n";
    }
    Tampil();
}

int sequential_search(const string& pencarian) {
    for (int i = pos - 1; i >= 0; --i) {
        if (dataATK[i].nama.find(pencarian) != string::npos ||
            dataATK[i].jenis.find(pencarian) != string::npos ||
            dataATK[i].jumlah.find(pencarian) != string::npos) {
            return i;
        }
    }
    return -1;
}

int binary_search(const string& pencarian) {
    int kiri = 0, kanan = pos - 1;
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        if (dataATK[tengah].nama == pencarian) {
            return tengah;
        } else if (dataATK[tengah].nama < pencarian) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}

void Cari() {
    if (pos > 0) {
        cin.ignore();
        string pencarian;
        cout << "Masukkan Kata Kunci Data ATK/S Pencarian: ";
        getline(cin, pencarian);

        int index;
        if (dataATK[0].nama < dataATK[pos - 1].nama) {
            index = binary_search(pencarian);
        } else {
            index = sequential_search(pencarian);
        }
        if (index != -1) {
            cout << "Data ATK/S ditemukan dalam indeks " << index + 1 << ": "
                 << "Nama ATK/S: " << dataATK[index].nama << endl;
            cout << "Jenis ATK/S: " << dataATK[index].jenis << endl;
            cout << "Jumlah ATK/S: " << dataATK[index].jumlah << endl;
        } else {
            cout << "Data ATK/S tidak dapat ditemukan, Silahkan coba lagi \n";
        }
    } else {
        cout << "Data ATK/S masih kosong\n";
    }
}

void Urut(data2* data, int metode) {
    Tampil();
    if (pos > 1) {
        switch (metode) {
            case 1 :
                sort(dataATK, dataATK + pos, [](const data2& a, const data2& b) {
                    return a.nama > b.nama;
                });
                cout << "Data ATK/S yang Telah diurutkan berdasarkan nama (Descending) \n";
                break;
            case 2:
                sort(dataATK, dataATK + pos, [](const data2& a, const data2& b) {
                    return stoi(a.jumlah) < stoi(b.jumlah);
                });
                cout << "Data ATK/S yang Telah diurutkan berdasarkan jumlah (Ascending) \n";
                break;
            case 3:
                cout << "Data ATK/S yang diurutkan dengan Selection Sorting \n";
                break;
            default:
                cout << "Pilihan tidak tersedia\n";
        }
    }
}

int Hitungjmlkar(data2* data, int index) {
    if (index < 0) {
        return 0;
    } else {
        return data[index].nama.length() + data[index].jenis.length() + data[index].jumlah.length() + Hitungjmlkar(data, index - 1);
    }
}

void JmlKarakData(data2* data) {
    cout << "Total jumlah karakter dari data ATK/S: " << Hitungjmlkar(data, pos - 1) << endl;
}

bool Login() {
    string Username, Password;
    cout << "=== Login ===\n";
    cout << "Username: ";
    getline(cin, Username);
    cout << "Password: ";
    getline(cin, Password);
    return Username == "nanda" && Password == "2309106022";
}

int main() {
    int percobaan = 0;
    while (percobaan < 3 && !Login()) {
        cout << "Login gagal. Kesempatan mencoba: " << 2 - percobaan << " kali\n";
        percobaan++;
    }

    if (percobaan == 3) {
        cout << "Percobaan Login telah melebihi batas, percobaan berhenti\n";
        return 0;
    }

    int pilihan;
    do {
        cout << "\n=== GUDANG PENDATAAN ATK/S ===\n"
             << "1. Tambah Data ATK/S\n"
             << "2. Ubah Data ATK/S\n"
             << "3. Hapus Data ATK/S\n"
             << "4. Tampilkan Data ATK/S\n"
             << "5. Cari Data ATK/S\n"
             << "6. Urut Data ATK/S\n"
             << "7. Jumlah Karakter Data ATK/S\n"
             << "8. Keluar\n"
             << "Pilih menu yang tertera diatas (1/2/3/4/5/6/7/8): ";
        cin >> pilihan;

        cin.ignore();

        switch (pilihan) {
            case 1: 
                Tambah(dataATK); 
                break;
            case 2: 
                Ubah(dataATK); 
                break;
            case 3: 
                Hapus(); 
                break;
            case 4: 
                Tampil(); 
                break;
            case 5:
                Cari();
                break;
            case 6:
                int metode;
                cout << "Pilih metode sorting yang diinginkan : \n"
                     << "1. Nama barang (Descending) \n"
                     << "2. Urutan angka barang (Ascending) \n"
                     << "3. Selection Sorting \n"
                     << "Pilih metode sorting yang diinginkan (1/2/3): ";
                cin >> metode;
                Urut(dataATK, metode);
                break;
            case 7:
                JmlKarakData(dataATK);
                break;
            case 8: 
                cout << "Terima kasih telah mendata program ATK/S\n"; 
                return 0;
            default: 
                cout << "Pilihan Invalid\n";
        }
    } while (true);

    return 0;
}
