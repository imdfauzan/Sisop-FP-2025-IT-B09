# Final Project Sistem Operasi IT

## Kelompok 3

| Nama                        | NRP        |
| --------------------------- | ---------- |
| Paundra Pujo Darmawan       | 5027241008 |
| Abiyyu Raihan Putra Wikanto | 5027241042 |
| Gemilang Ananda Lingua      | 5027241072 |
| Imam Mahmud Dalil Fauzan    | 5027241100 |

## Deskripsi Soal

**Process Exit Status Tracker (9)**

Buatlah sebuah program yang memanfaatkan `fork()` untuk membuat satu child process, lalu jalankan dua skenario berbeda:
(1) Child keluar secara normal dengan exit code tertentu, dan
(2) Child keluar akibat menerima sinyal (misal dengan raise `(SIGSEGV)`).
Parent process wajib menunggu child dengan wait, kemudian menampilkan ke layar status keluar child: apakah keluar normal (tampilkan exit code-nya) atau akibat sinyal (tampilkan nomor sinyalnya). Pastikan output membedakan kedua kasus ini dengan jelas, sehingga mudah dipahami.

### Catatan

Soal ini dikerjakan menggunakan bahasa C di lingkungan WSL, dengan fokus pada penggunaan `fork()`, `wait()`, dan analisis status keluar child process. Program dibagi menjadi dua skenario; 1.) proses yang keluar secara normal dan 2.) yang dihentikan oleh sinyal. Pendekatan ini membantu memahami manajemen proses dasar dalam sistem operasi, terutama cara parent memantau dan membedakan hasil eksekusi child-nya.

Struktur repository:

```
assets
└── demo1.mp4
main.c
main
README.md
```

## Pengerjaan

**1. `fork()` — Membuat Proses Anak.**

> Poin Soal = Program membuat satu child process menggunakan `fork()`

**Teori**

Berdasarkan Dokumentasi Linux, `fork()` membuat proses baru (dinamakan child) yang merupakan duplikat dari proses pemanggil (parent), dengan ruang memori dan descriptor file tersendiri.

Contoh: Kamu sedang menjalankan satu program (misalnya `./fpsisop`). Ini disebut _parent process_. Ketika `fork()` dipanggil, Sistem akan membuat duplikat dari proses itu, seperti memfotokopi. Hasil Fotokopiannya disebut child process.

> "`fork()` creates a new process by duplicating the calling process. The new process, referred to as the child..." [1]

**Solusi**

Kode program memanggil `fork()` dalam dua fungsi utama:

```
pid_t pid = fork();
```

Kemudian proses dibedakan:

```
if (pid == 0) {
// child process
} else if (pid > 0) {
// parent process
} else {
perror("fork"); // jika fork gagal
}
```

**2. `wait()` dan `waitpid()` — Menunggu Proses Anak.**

> Poin Soal = Parent wajib menunggu child selesai menggunakan `wait()`.

**Teori**

`wait()` adalah fungsi yang digunakan parent process untuk menunda eksekusi parent sampai child berakhir, lalu mengisi status ke variabel integer yang bisa diperiksa menggunakan makro tertentu.

> "The `wait()` function obtains status information for process termination from any child process. The `waitpid()` function obtains status information for process termination, and optionally process stop and/or continue, from a specified subset of the child processes." [2]

```
int status;
wait(&status);
```

Setelah `wait()`, status child menjadi :

- `WIFEXITED(status)` → true jika child keluar dengan normal (`exit()`).
- `WIFSIGNALED(status)` → true kalau child mati karena sinyal (SIGSEGV, SIGKILL, dll).

**Solusi**

Kedua fungsi utama menunggu child menggunakan:
```
int status;
wait(&status);
```
Setelah itu, parent memeriksa status dengan logika kondisional:
```
if (WIFEXITED(status)) { ... }
else if (WIFSIGNALED(status)) { ... }
```

**3. Makro Status: WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG**

> Poin Soal = Tampilkan ke layar status keluar child (exit code atau sinyal)

**Teori**

- `WIFEXITED(status)` → true jika child keluar normal
- `WEXITSTATUS(status)` → mengambil nilai exit code (hanya jika WIFEXITED true)
- `WIFSIGNALED(status)` → true jika child selesai karena sinyal
- `WTERMSIG(status)` → mengambil nomor sinyal penyebab terminasi

> Sumber [3]

**Solusi**

Output yang dihasilkan jelas membedakan:

- [Parent] Child keluar normal dengan kode: 42
atau:
- [Parent] Child dihentikan oleh sinyal: 11 (Segmentation fault)

Semua output disusun agar skenario 1 dan 2 mudah dibaca dan dibedakan.

**4. Sinyal & `SIGSEGV`.**

> Poin Soal = Jalankan dua skenario: (1) child keluar dengan exit() dan (2) keluar karena sinyal (SIGSEGV)

**Teori**

Fungsi `exit(code)` digunakan agar proses keluar dengan status tertentu. Ketika parent menunggu child, parent dapat mengetahui nilai kode ini melalui `wait()` dan makro `WEXITSTATUS()`.

`SIGSEGV` (Segmentation Fault) adalah sinyal (signal) yang dikirim ke proses saat dia mengakses memori yang tidak seharusnya dia akses (illegal). Biasa dikenal segmentation fault. Dalam kode, bisa dipicu manual dengan `raise(SIGSEGV)`.

Contoh:
Kamu mencoba akses alamat memori kosong atau menulis ke alamat 0, sistem akan menghentikan prosesmu.

`raise(SIGSEGV)` secara manual mengirim sinyal segfault ke diri sendiri.
Tujuannya (di tugas ini) untuk mensimulasikan child process yang mati karena kesalahan serius (bukan karena `exit()` biasa).

**Solusi**

Skenario 1: child keluar dengan `exit(42)`:
```
printf("[Child] Keluar normal dengan exit code 42.\n");
exit(42);
```

Parent akan mendeteksi ini dengan:
```
if (WIFEXITED(status)) {
printf("[Parent] Child keluar normal dengan kode: %d\n", WEXITSTATUS(status));
}
```

Skenario 2: child mati karena sinyal:
```
printf("[Child] Akan menyebabkan segfault (SIGSEGV)...\n");
raise(SIGSEGV);
```

Parent akan mendeteksinya dengan:
```
if (WIFSIGNALED(status)) {
printf("[Parent] Child dihentikan oleh sinyal: %d (%s)\n",
WTERMSIG(status), strsignal(WTERMSIG(status)));
}
```

**Video Menjalankan Program**

[Video Demo](assets/demo1.mp4)

## Daftar Pustaka

1. [1] https://linux.die.net/man/2/fork
2. [2] https://pubs.opengroup.org/onlinepubs/9699919799/functions/wait.html
3. [3] https://man7.org/linux/man-pages/man2/wait.2.html
