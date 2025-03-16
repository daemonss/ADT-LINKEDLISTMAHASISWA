#ifndef MAHASISWA_H
#define MAHASISWA_H
#define MAX_NAMA 50

// Definisi struktur data Mahasiswa
typedef struct {
    char nama[MAX_NAMA];  // Menyimpan nama mahasiswa
    int nilaiUTS;         // Menyimpan nilai UTS mahasiswa
} Mahasiswa;

// Definisi struktur elemen list
typedef struct tElmtList *address;
typedef struct tElmtList {
    Mahasiswa info;  // Data mahasiswa
    address next;    // Pointer ke elemen berikutnya
} ElmtList;

// Definisi list
typedef struct {
    address First;  // Pointer ke elemen pertama list
} List;

//Deklarasi Fungsi//
List createList();                   // Constructor: Membuat list kosong
void deleteList(List *L);            // Destructor: Menghapus seluruh elemen list
int isEmpty(List L);                 // Validator: Memeriksa apakah list kosong
Mahasiswa getElement(address P);     // Getter: Mengambil data dari node tertentu
void printList(List L);              // PrintObject: Menampilkan seluruh isi list

void insertAscendingByName(List *L, Mahasiswa m);  // Menyisipkan elemen secara terurut berdasarkan nama (case-insensitive)
void copyHighScore(List L1, List *L2);            // Menyalin elemen dengan nilai > 70 ke list baru
void removeDuplicates(List *L);                   // Menghapus duplikat nama dalam list (case-insensitive)
void sortByNilaiDescending(List L);               // Mengurutkan list berdasarkan nilai (descending)
int countElements(List L);                        // Menghitung jumlah elemen dalam list
void clearBuffer();                               // Membersihkan buffer input
void waitForEnter();                              // Menunggu pengguna menekan Enter
void clearScreen();                               // Membersihkan layar terminal
void displayMenu();                               // Menampilkan menu pilihan
void inputMahasiswa(List *L);                     // Menerima input mahasiswa dari pengguna

/* FUNGSI AKSESOR */
#define info(P) (P)->info
#define nama(I) (I).nama
#define nilai(I) (I).nilaiUTS
#define next(P) (P)->next
#define first(L) (L).First

#endif