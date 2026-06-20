#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Pertemuan 3 : Namespace
namespace Pelelangan {

    // Struct Data Barang
    struct BarangAntik {
        int id;
        string nama;
        string kategori;
        long long hargaAwal;
        long long tawaranTertinggi;
        string penawarTertinggi;
    };

    // Pertemuan 10 : STL Vector
    vector<BarangAntik> daftarBarang;
    vector<BarangAntik> riwayatPemenang;

    int nextID = 1;

    // Pertemuan 5 : Inline Function
    inline void garis() {
        cout << "\n=========================================\n";
    }

    // Pertemuan 4 : Function Tambah Barang
    void tambahBarang() {

        BarangAntik b;

        b.id = nextID++;

        cin.ignore();

        cout << "\nNama Barang     : ";
        getline(cin, b.nama);

        cout << "Kategori        : ";
        getline(cin, b.kategori);

        cout << "Harga Awal (Rp) : ";
        cin >> b.hargaAwal;

        b.tawaranTertinggi = b.hargaAwal;
        b.penawarTertinggi = "Belum Ada";

        daftarBarang.push_back(b);

        cout << "\nBarang berhasil ditambahkan!\n";
    }

    // Pertemuan 4 : Function Tampilkan Barang
    void tampilkanBarang() {

        if (daftarBarang.empty()) {
            cout << "\nBelum ada barang aktif.\n";
            return;
        }

        garis();

        // Pertemuan 11 : Iterator
        vector<BarangAntik>::iterator it;

        for(it = daftarBarang.begin();
            it != daftarBarang.end();
            it++) {

            cout << "\nID                : "
                 << it->id << endl;

            cout << "Nama Barang       : "
                 << it->nama << endl;

            cout << "Kategori          : "
                 << it->kategori << endl;

            cout << "Harga Awal        : Rp "
                 << it->hargaAwal << endl;

            cout << "Tawaran Tertinggi : Rp "
                 << it->tawaranTertinggi << endl;

            cout << "Penawar           : "
                 << it->penawarTertinggi << endl;
        }
    }

    // Pertemuan 6 : Overloading Function Cari Berdasarkan ID
    void cariBarang(string nama) {

        auto it = find_if(
            daftarBarang.begin(),
            daftarBarang.end(),
            [&](BarangAntik b) {
                return b.nama == nama;
            });

        if(it != daftarBarang.end()) {

            cout << "\nBarang Ditemukan\n";
            cout << "ID : "
                 << it->id << endl;

            cout << "Kategori : "
                 << it->kategori << endl;
        }
        else {
            cout << "\nBarang tidak ditemukan.\n";
        }
    }

    // Pertemuan 6 : Overloading Function Cari Berdasarkan ID
    void cariBarang(int id) {

        auto it = find_if(
            daftarBarang.begin(),
            daftarBarang.end(),
            [&](BarangAntik b) {
                return b.id == id;
            });

        if(it != daftarBarang.end()) {

            cout << "\nBarang Ditemukan\n";
            cout << "Nama : "<< it->nama << endl;
        }
        else {
            cout << "\nBarang tidak ditemukan.\n";
        }
    }

    // Pertemuan 2 : Reference
    void lakukanPenawaran(BarangAntik &barang) {

        string namaPenawar;
        long long tawaran;

        cin.ignore();

        cout << "\nNama Penawar : ";
        getline(cin, namaPenawar);

        cout << "Nilai Tawaran (Rp) : ";
        cin >> tawaran;

        try {

            // Pertemuan 9 : Exception Handling
            if(tawaran <= barang.tawaranTertinggi)
                throw "Tawaran harus lebih tinggi!";

            barang.tawaranTertinggi = tawaran;
            barang.penawarTertinggi = namaPenawar;
            ofstream file("riwayat_tawar.txt", ios::app);

            file << "ID Barang : " << barang.id
                << " | Nama Barang : " << barang.nama
                << " | Penawar : " << namaPenawar
                << " | Tawaran : Rp " << tawaran
                << endl;

file.close();

            cout << "\nTawaran berhasil diterima.\n";
        }

        catch(const char *pesan) {

            cout << "\nError : "
                 << pesan << endl;
        }
    }

    // Pertemuan 2 : Pointer
    void pilihBarangLelang() {

        if(daftarBarang.empty()) {

            cout << "\nBelum ada barang.\n";
            return;
        }

        int id;

        tampilkanBarang();

        cout << "\nMasukkan ID Barang : ";
        cin >> id;

        for(size_t i=0;i<daftarBarang.size();i++) {

            if(daftarBarang[i].id == id) {

                BarangAntik *ptr =
                    &daftarBarang[i];

                lakukanPenawaran(*ptr);
                return;
            }
        }

        cout << "\nID tidak ditemukan.\n";
    }

    // Menu Baru : Tutup Pelelangan
    void tutupPelelangan() {

        if(daftarBarang.empty()) {

            cout << "\nTidak ada barang aktif.\n";
            return;
        }

        int id;

        tampilkanBarang();

        cout << "\nID Barang Yang Ditutup : ";
        cin >> id;

        for(auto it = daftarBarang.begin();
            it != daftarBarang.end();
            it++) {

            if(it->id == id) {

                cout << "\nPELELANGAN DITUTUP\n";

                cout << "Barang    : "
                     << it->nama << endl;

                cout << "Pemenang  : "
                     << it->penawarTertinggi
                     << endl;

                cout << "Harga     : Rp "
                     << it->tawaranTertinggi
                     << endl;

                riwayatPemenang.push_back(*it);

                ofstream file(
                    "riwayat_pemenang.txt",
                    ios::app);

                file << it->id << ";"
                     << it->nama << ";"
                     << it->penawarTertinggi
                     << ";"
                     << it->tawaranTertinggi
                     << endl;

                file.close();

                daftarBarang.erase(it);

                cout << "\nBarang dipindahkan ke riwayat.\n";

                return;
            }
        }

        cout << "\nID tidak ditemukan.\n";
    }

    // Riwayat Pemenang
    void tampilkanRiwayat()
{
    ifstream file("riwayat_pemenang.txt");

    if(!file)
    {
        cout << "\nBelum ada riwayat pemenang.\n";
        return;
    }

    string baris;

    garis();
    cout << "\n             RIWAYAT PEMENANG LELANG           \n"<<endl;

    while(getline(file, baris))
    {
        cout << baris << endl;
    }

    file.close();
    }

    // Pertemuan 12 : Sort + Lambda
    void statistik() {

        if(daftarBarang.empty()) {

            cout << "\nTidak ada data.\n";
            return;
        }

        sort(
            daftarBarang.begin(),
            daftarBarang.end(),

            [](BarangAntik a,
               BarangAntik b) {

                return a.hargaAwal <
                       b.hargaAwal;
            });

        cout << "\nBarang berhasil diurutkan.\n";

        int jumlahDitawar = count_if(
            daftarBarang.begin(),
            daftarBarang.end(),

            [](BarangAntik b) {

                return b.penawarTertinggi
                       != "Belum Ada";
            });

        cout << "Jumlah barang yang sudah ditawar : "
             << jumlahDitawar << endl;
    }

    // Pertemuan 13 : File Handling Simpan
    void simpanData() {

        ofstream file("pelelangan.txt");

        for(auto b : daftarBarang) {

            file << b.id << ";"
                 << b.nama << ";"
                 << b.kategori << ";"
                 << b.hargaAwal << ";"
                 << b.tawaranTertinggi << ";"
                 << b.penawarTertinggi
                 << endl;
        }

        file.close();

        cout << "\nData berhasil disimpan.\n";
    }
    void tampilkanRiwayatTawar(){
        ifstream file("riwayat_tawar.txt");

        if(!file)
        {
            cout << "\nBelum ada riwayat penawaran.\n";
            return;
        }

        string baris;

        while(getline(file, baris))
        {
            cout << baris << endl;
        }

        file.close();
    }

    //Pertemuan 13 - File Handling memuat DAta dari file ke vector saat program dijalankan
    void loadData(){
        ifstream file("pelelangan.txt");
        if(!file)
            return;
        string baris;
        while(getline(file,baris))
        {
            stringstream ss(baris);
            BarangAntik b;
            string idStr;
            string hargaStr;
            string tawaranStr;

            getline(ss, idStr, ';');
            getline(ss, b.nama, ';');
            getline(ss, b.kategori, ';');
            getline(ss, hargaStr, ';');
            getline(ss, tawaranStr, ';');
            getline(ss, b.penawarTertinggi);

            b.id = stoi(idStr);
            b.hargaAwal = stoll(hargaStr);
            b.tawaranTertinggi = stoll(tawaranStr);

            daftarBarang.push_back(b);
            if(b.id >= nextID)
                nextID = b.id + 1;
        }
        file.close();
    }

}
int main() {

    using namespace Pelelangan;

    int menu;
    loadData();
    do {

        garis();

        cout << " SISTEM PELELANGAN BARANG ANTIK\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang Aktif\n";
        cout << "3. Cari Barang\n";
        cout << "4. Lakukan Penawaran\n";
        cout << "5. Tampilkan Riwayat Tawar\n";
        cout << "6. Riwayat Pemenang\n";
        cout << "7. Statistik\n";
        cout << "8. Simpan Data\n";
        cout << "9. Tutup Pelelangan\n";
        cout << "0. Keluar\n";
        cout << "=========================================";

        cout << "\nPilih Menu : ";
        cin >> menu;

        switch(menu) {

        case 1:
            tambahBarang();
            break;

        case 2:
            tampilkanBarang();
            break;

        case 3: {

            string nama;

            cin.ignore();

            cout << "Nama Barang : ";
            getline(cin,nama);

            cariBarang(nama);
            break;
        }

        case 4:
            pilihBarangLelang();
            break;

        case 5:
            tampilkanRiwayatTawar();
            break;

        case 6:
            tampilkanRiwayat();
            break;

        case 7:
            statistik();
            break;

        case 8:
            simpanData();
            break;

        case 9:
            tutupPelelangan();
            break;

        case 0:
            cout << "\nProgram selesai.\n";
            break;

        default:
            cout << "\nMenu tidak tersedia.\n";
        }

    } while(menu != 0);

    return 0;
}