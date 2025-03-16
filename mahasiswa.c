#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mahasiswa.h"

// 1. Constructor: Membuat list kosong
List createList() {
    List L;
    first(L) = NULL;  // Set First ke NULL karena list masih kosong
    return L;
}

// 2. Destructor: Menghapus seluruh elemen list
void deleteList(List *L) {
    address P = first(*L);
    while (P != NULL) {
        address temp = P;  // Simpan alamat elemen saat ini
        P = next(P);       // Pindah ke elemen berikutnya
        free(temp);        // Bebaskan memori elemen saat ini
    }
    first(*L) = NULL;  // Set First ke NULL karena list sudah kosong
}

// 3. Validator: Memeriksa apakah list kosong
int isEmpty(List L) {
    return (first(L) == NULL);  // Return 1 jika list kosong, 0 jika tidak
}

// 4. Getter: Mengambil data dari node tertentu
Mahasiswa getElement(address P) {
    return info(P);  
}

// 5. PrintObject: Menampilkan seluruh isi list
void printList(List L) {
    if (isEmpty(L)) {
        printf("List kosong\n");
        return;
    }

    address P = first(L);
    printf("%-20s | %-4s\n", "Nama", "Nilai");
    printf("---------------------|------\n");
    while (P != NULL) {
        Mahasiswa m = getElement(P);
        printf("%-20s | %-4d\n", nama(m), nilai(m));
        P = next(P);
    }
}

// Menampilkan menu pilihan
void displayMenu() {
    clearScreen();
    printf("\n=== Link-List Mahasiswa ===\n");
    printf("1. Tambah Mahasiswa ke L1\n");
    printf("2. Tampilkan L1 (Urut Nama)\n");
    printf("3. Tampilkan L1 (Urut Nilai)\n");
    printf("4. Salin ke L2 (Nilai > 70)\n");
    printf("5. Tampilkan L2\n");
    printf("6. Hitung Jumlah Mahasiswa\n");
    printf("7. Hapus Duplikat di L2\n");
    printf("8. Hapus Semua List\n");
    printf("9. Keluar\n");
    printf("Pilihan: ");
}

// Menerima input mahasiswa dari pengguna
void inputMahasiswa(List *L) {
    Mahasiswa m;

    printf("\nMasukkan nama mahasiswa: ");
    fgets(nama(m), MAX_NAMA, stdin);
    nama(m)[strcspn(nama(m), "\n")] = '\0';

    do {
        printf("Masukkan nilai UTS (0-100): ");
        scanf("%d", &nilai(m));
        clearBuffer();
        if (nilai(m) < 0 || nilai(m) > 100) {
            printf("Nilai harus antara 0-100!\n");
        }
    } while (nilai(m) < 0 || nilai(m) > 100);

    insertAscendingByName(L, m); 
    printf("\nData berhasil ditambahkan!");
}

// Menyisipkan elemen secara terurut berdasarkan nama (case-insensitive)
void insertAscendingByName(List *L, Mahasiswa m) {
    address newNode = (address)malloc(sizeof(ElmtList));
    if (newNode == NULL) {
        printf("Alokasi memori gagal!\n");
        return;
    }

    strcpy(nama(info(newNode)), nama(m));  
    nilai(info(newNode)) = nilai(m);       
    next(newNode) = NULL;                  

    if (isEmpty(*L)) {
        first(*L) = newNode;  
    } else if (strcasecmp(nama(m), nama(info(first(*L)))) < 0) {
        next(newNode) = first(*L); 
        first(*L) = newNode;
    } else {
        address curr = first(*L);
        address prev = NULL;


        while (curr != NULL && strcasecmp(nama(m), nama(info(curr))) >= 0) {
            if (strcasecmp(nama(m), nama(info(curr))) == 0) {
                printf("Nama sudah ada dalam list!\n");
                free(newNode); 
                return;
            }
            prev = curr;
            curr = next(curr);
        }


        next(newNode) = curr;
        next(prev) = newNode;
    }
}

// Menyalin elemen dengan nilai > 70 ke list baru
void copyHighScore(List L1, List *L2) {
    address P = first(L1);
    while (P != NULL) {
        if (nilai(info(P)) > 70) {
            insertAscendingByName(L2, info(P));  // Salin elemen ke L2 jika nilai > 70
        }
        P = next(P);
    }
}

// Menghapus duplikat nama dalam list (case-insensitive)
void removeDuplicates(List *L) {
    address curr = first(*L);
    while (curr != NULL && next(curr) != NULL) {
        if (strcasecmp(nama(info(curr)), nama(info(next(curr)))) == 0) {
            address temp = next(curr);  
            next(curr) = next(temp);   
            free(temp);               
        } else {
            curr = next(curr); 
        }
    }
}

// Mengurutkan list berdasarkan nilai (descending)
void sortByNilaiDescending(List L) {
    if (isEmpty(L)) return;

    address P = first(L);
    int count = countElements(L);
    Mahasiswa *arr = (Mahasiswa *)malloc(count * sizeof(Mahasiswa));

    // Salin data dari list ke array
    for (int i = 0; i < count; i++) {
        arr[i] = info(P);
        P = next(P);
    }

    // Urutkan array secara descending menggunakan bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (nilai(arr[j]) < nilai(arr[j + 1])) {
                Mahasiswa temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Tampilkan array yang sudah diurutkan
    printf("%-20s | %-4s\n", "Nama", "Nilai");
    printf("---------------------|------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s | %-4d\n", nama(arr[i]), nilai(arr[i]));
    }

    free(arr);  // Bebaskan memori array
}

// Menghitung jumlah elemen dalam list
int countElements(List L) {
    int count = 0;
    address P = first(L);
    while (P != NULL) {
        count++;
        P = next(P);
    }
    return count;
}

// Membersihkan buffer input
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menunggu pengguna menekan Enter
void waitForEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}

// Membersihkan layar terminal
void clearScreen() {
    system("clear");
}