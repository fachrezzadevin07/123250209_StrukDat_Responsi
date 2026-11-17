//Fachrezza Devin Rasendrya Prathama
//123250209

#include <iostream>
#include <string>
using namespace std;

struct Energi {
    int kode;
    string nama;
    Energi *next;
};

struct Organ {
    int kode;
    string nama;
    Organ *kiri;
    Organ *kanan;
};

Energi *depan = NULL;     
Energi *belakang = NULL;  
Energi *riwayat = NULL;   
Organ *akar = NULL;       


bool bacaAngka(string teks, int &hasil) {
    cout << teks;
    string s;
    getline(cin, s);
    if (s.empty() || s.length() > 9) return false;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    hasil = stoi(s);
    return true;
}

bool adaDiAntrean(int kode) {
    for (Energi *p = depan; p != NULL; p = p->next)
        if (p->kode == kode) return true;
    return false;
}

bool adaDiRiwayat(int kode) {
    for (Energi *p = riwayat; p != NULL; p = p->next)
        if (p->kode == kode) return true;
    return false;
}

Organ *cariOrgan(Organ *node, int kode) {
    if (node == NULL || node->kode == kode) return node;
    if (kode < node->kode) return cariOrgan(node->kiri, kode);
    return cariOrgan(node->kanan, kode);
}

bool kodeSudahDipakai(int kode) {
    return adaDiAntrean(kode) || adaDiRiwayat(kode) || cariOrgan(akar, kode) != NULL;
}

Organ *sisipOrgan(Organ *node, int kode, string nama) {
    if (node == NULL) {
        Organ *baru = new Organ;
        baru->kode = kode;
        baru->nama = nama;
        baru->kiri = NULL;
        baru->kanan = NULL;
        return baru;
    }
    if (kode < node->kode) node->kiri = sisipOrgan(node->kiri, kode, nama);
    else node->kanan = sisipOrgan(node->kanan, kode, nama);
    return node;
}

Organ *hapusOrgan(Organ *node, int kode) {
    if (node == NULL) return NULL;

    if (kode < node->kode) {
        node->kiri = hapusOrgan(node->kiri, kode);
    } else if (kode > node->kode) {
        node->kanan = hapusOrgan(node->kanan, kode);
    } else {
        if (node->kiri == NULL && node->kanan == NULL) {
            delete node;
            return NULL;
        }
        if (node->kiri == NULL) {
            Organ *temp = node->kanan;
            delete node;
            return temp;
        }
        if (node->kanan == NULL) {
            Organ *temp = node->kiri;
            delete node;
            return temp;
        }
        Organ *suksesor = node->kanan;
        while (suksesor->kiri != NULL) suksesor = suksesor->kiri;
        node->kode = suksesor->kode;
        node->nama = suksesor->nama;
        node->kanan = hapusOrgan(node->kanan, suksesor->kode);
    }
    return node;
}

void preOrder(Organ *node, int &no) {
    if (node == NULL) return;
    cout << ++no << ". [" << node->kode << "] " << node->nama << endl;
    preOrder(node->kiri, no);
    preOrder(node->kanan, no);
}

void inOrder(Organ *node, int &no) {
    if (node == NULL) return;
    inOrder(node->kiri, no);
    cout << ++no << ". [" << node->kode << "] " << node->nama << endl;
    inOrder(node->kanan, no);
}

void postOrder(Organ *node, int &no) {
    if (node == NULL) return;
    postOrder(node->kiri, no);
    postOrder(node->kanan, no);
    cout << ++no << ". [" << node->kode << "] " << node->nama << endl;
}

void hapusSemuaOrgan(Organ *node) {
    if (node == NULL) return;
    hapusSemuaOrgan(node->kiri);
    hapusSemuaOrgan(node->kanan);
    delete node;
}

void tampilMenu() {
    cout << "\n=== Sistem Organ Inti Nirwana ===\n\n";
    cout << "1. Tambah Energi\n";
    cout << "2. Lihat Energi Dalam Antrean\n";
    cout << "3. Proses Energi\n";
    cout << "4. Lihat Energi Yang Sudah Terserap\n";
    cout << "5. Hapus Riwayat Energi Teratas\n";
    cout << "6. Cari Energi Di Organ\n";
    cout << "7. Lihat Isi Organ\n";
    cout << "8. Gunakan Energi\n";
    cout << "9. Keluar\n\n";
}

void tambahEnergi() {
    string lagi = "y";
    while (lagi == "y" || lagi == "Y") {
        int kode;
        if (!bacaAngka("Masukkan kode energi: ", kode) || kode <= 0) {
            cout << "Kode energi harus angka lebih dari 0!\n";
            continue;
        }
        if (kodeSudahDipakai(kode)) {
            cout << "Kode energi " << kode << " sudah ada!\n";
            continue;
        }

        string nama;
        cout << "Masukkan nama energi: ";
        getline(cin, nama);
        if (nama.empty()) {
            cout << "Nama energi tidak boleh kosong!\n";
            continue;
        }

        Energi *baru = new Energi;
        baru->kode = kode;
        baru->nama = nama;
        baru->next = NULL;
        if (depan == NULL) {
            depan = baru;
            belakang = baru;
        } else {
            belakang->next = baru;
            belakang = baru;
        }
        cout << "Berhasil memasukkan energi!\n";

        while (true) {
            cout << "\nApakah anda ingin menambahkan energi lagi? (y/n): ";
            getline(cin, lagi);
            if (lagi == "y" || lagi == "Y" || lagi == "n" || lagi == "N") break;
            cout << "Pilihan tidak valid, masukkan y atau n!\n";
        }
    }
}

void lihatAntrean() {
    if (depan == NULL) {
        cout << "Antrean energi kosong!\n";
        return;
    }
    cout << "=== Energi Dalam Antrean ===\n\n";
    int no = 0;
    for (Energi *p = depan; p != NULL; p = p->next)
        cout << ++no << ". [" << p->kode << "] " << p->nama << endl;
}

void prosesEnergi() {
    if (depan == NULL) {
        cout << "Tidak ada energi dalam antrean untuk diproses!\n";
        return;
    }

    
    Energi *diproses = depan;
    depan = depan->next;
    if (depan == NULL) belakang = NULL;

    Energi *r = new Energi;
    r->kode = diproses->kode;
    r->nama = diproses->nama;
    r->next = riwayat;
    riwayat = r;

    akar = sisipOrgan(akar, diproses->kode, diproses->nama);

    cout << "Berhasil memproses energi " << diproses->nama << "!\n";
    delete diproses;
}

void lihatRiwayat() {
    if (riwayat == NULL) {
        cout << "Belum ada energi yang terserap!\n";
        return;
    }
    cout << "=== Energi Yang Sudah Terserap ===\n\n";
    int no = 0;
    for (Energi *p = riwayat; p != NULL; p = p->next)
        cout << ++no << ". [" << p->kode << "] " << p->nama << endl;
}

void hapusRiwayatTeratas() {
    if (riwayat == NULL) {
        cout << "Riwayat energi masih kosong!\n";
        return;
    }
    Energi *hapus = riwayat;
    riwayat = riwayat->next;
    cout << "Riwayat energi " << hapus->nama << " teratas telah dihapus!\n";
    delete hapus;
}

void cariEnergi() {
    if (akar == NULL) {
        cout << "Organ masih kosong!\n";
        return;
    }
    int kode;
    if (!bacaAngka("Masukkan kode energi: ", kode) || kode <= 0) {
        cout << "Kode energi tidak valid!\n";
        return;
    }
    Organ *hasil = cariOrgan(akar, kode);
    if (hasil == NULL) cout << "Energi dengan kode " << kode << " tidak ditemukan di organ!\n";
    else cout << "Ditemukan: [" << hasil->kode << "] " << hasil->nama << endl;
}

void lihatIsiOrgan() {
    if (akar == NULL) {
        cout << "Organ masih kosong!\n";
        return;
    }
    cout << "=== Isi Kristal Organ ===\n\n";
    cout << "1. Pre-order\n2. In-order\n3. Post-order\n\n";
    int pilih;
    if (!bacaAngka("Masukkan pilihan anda: ", pilih) || pilih < 1 || pilih > 3) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    cout << endl;
    int no = 0;
    if (pilih == 1) preOrder(akar, no);
    else if (pilih == 2) inOrder(akar, no);
    else postOrder(akar, no);
}

void gunakanEnergi() {
    if (akar == NULL) {
        cout << "Organ masih kosong!\n";
        return;
    }
    int kode;
    if (!bacaAngka("Masukkan kode energi: ", kode) || kode <= 0) {
        cout << "Kode energi tidak valid!\n";
        return;
    }
    Organ *target = cariOrgan(akar, kode);
    if (target == NULL) {
        cout << "Energi dengan kode " << kode << " tidak ada di organ!\n";
        return;
    }
    string nama = target->nama;
    akar = hapusOrgan(akar, kode);
    cout << "Energi " << nama << " telah digunakan!\n";
}


int main() {
    int pilihan;
    do {
        tampilMenu();
        if (!bacaAngka("Masukkan pilihan anda: ", pilihan)) {
            cout << "Pilihan tidak valid, masukkan angka 1-9!\n";
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
            case 1: tambahEnergi(); break;
            case 2: lihatAntrean(); break;
            case 3: prosesEnergi(); break;
            case 4: lihatRiwayat(); break;
            case 5: hapusRiwayatTeratas(); break;
            case 6: cariEnergi(); break;
            case 7: lihatIsiOrgan(); break;
            case 8: gunakanEnergi(); break;
            case 9: cout << "Terima kasih, sampai jumpa!\n"; break;
            default: cout << "Pilihan tidak valid, masukkan angka 1-9!\n";
        }
    } while (pilihan != 9);

    while (depan != NULL) {
        Energi *t = depan;
        depan = depan->next;
        delete t;
    }
    while (riwayat != NULL) {
        Energi *t = riwayat;
        riwayat = riwayat->next;
        delete t;
    }
    hapusSemuaOrgan(akar);

    return 0;
}


 
