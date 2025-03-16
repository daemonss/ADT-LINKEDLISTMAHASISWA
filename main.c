//Maaf pak sebelumnya saya menggunakan vscode karena device saya tidak mendukung untuk mendownload Devc++//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mahasiswa.h"

int main() {
    // Inisialisasi list menggunakan constructor
    List L1 = createList();
    List L2 = createList();

    int pilihan;
    char konfirmasi;

    do {
        displayMenu();
        scanf(" %d", &pilihan);
        clearBuffer();

        switch (pilihan) {
            case 1: {
                inputMahasiswa(&L1);
                waitForEnter();
                break;
            }
            case 2: {
                printf("\n=== LIST L1 (Urut Nama) ===\n");
                printList(L1);
                waitForEnter();
                break;
            }
            case 3: {
                printf("\n=== LIST L1 (Urut Nilai) ===\n");
                sortByNilaiDescending(L1);
                waitForEnter();
                break;
            }
            case 4: {
                deleteList(&L2);
                L2 = createList();
                copyHighScore(L1, &L2);
                printf("\nData dengan nilai >70 telah disalin ke L2");
                waitForEnter();
                break;
            }
            case 5: {
                printf("\n=== LIST L2 ===\n");
                printList(L2);
                waitForEnter();
                break;
            }
            case 6: {
                printf("\n=== JUMLAH MAHASISWA ===\n");
                printf("Jumlah di L1: %d\n", countElements(L1));
                printf("Jumlah di L2: %d\n", countElements(L2));
                waitForEnter();
                break;
            }
            case 7: {
                removeDuplicates(&L2);
                printf("\nDuplikat nama di L2 telah dihapus");
                waitForEnter();
                break;
            }
            case 8: {
                printf("\nYakin ingin menghapus semua data? (y/n): ");
                scanf("%c", &konfirmasi);
                if (tolower(konfirmasi) == 'y') {
                    deleteList(&L1);
                    deleteList(&L2);
                    L1 = createList();
                    L2 = createList();
                    printf("Semua data telah dihapus");
                }
                waitForEnter();
                break;
            }
            case 9: {
                printf("\nTerima kasih!\n");
                break;
            }
            default: {
                printf("\nPilihan tidak valid!");
                waitForEnter();
            }
        }
    } while (pilihan != 9);

    // Membersihkan memori menggunakan destructor
    deleteList(&L1);
    deleteList(&L2);
    return 0;
}