# Final Project Sistem Operasi IT

## Peraturan

1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok 9

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

> Insert catatan dari pengerjaan kalian... (contoh dibawah) // hapus line ini

Struktur repository:

```
.
..
```

## Pengerjaan

> Insert poin soal...

**Teori**

1. `fork()` — Membuat Proses Anak.

Berdasarkan Dokumentasi Linux, `fork()` membuat proses baru (dinamakan child) yang merupakan duplikat dari proses pemanggil (parent), dengan ruang memori dan descriptor file tersendiri.

Contoh: Kamu sedang menjalankan satu program (misalnya ./fpsisop). Ini disebut _parent process_. Ketika `fork()` dipanggil, Sistem akan membuat duplikat dari proses itu, seperti memfotokopi. Hasil Fotokopiannya disebut child process.

> "fork() creates a new process by duplicating the calling process. The new process, referred to as the child..." [1]

2. `wait()` dan `waitpid()` — Menunggu Proses Anak.

`wait()` adalah fungsi yang digunakan parent process untuk menunda eksekusi parent sampai child berakhir, lalu mengisi status ke variabel integer yang bisa diperiksa menggunakan makro tertentu

```
int status;
wait(&status);
```

Setelah `wait()`, status child menjadi :

- `WIFEXITED(status)` → true jika child keluar dengan normal (`exit()`).
- `WIFSIGNALED(status)` → true kalau child mati karena sinyal (SIGSEGV, SIGKILL, dll).

3. Makro Status: WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG

- `WIFEXITED(status)` → true jika child keluar normal
- `WEXITSTATUS(status)` → mengambil nilai exit code (hanya jika WIFEXITED true)
- `WIFSIGNALED(status)` → true jika child selesai karena sinyal
- `WTERMSIG(status)` → mengambil nomor sinyal penyebab terminasi

> Sumber [2]

4. Sinyal & `SIGSEGV`.

`SIGSEGV` (Segmentation Fault) adalah sinyal (signal) yang dikirim ke proses saat dia mengakses memori yang tidak seharusnya dia akses (illegal). Biasa dikenal segmentation fault. Dalam kode, bisa dipicu manual dengan `raise(SIGSEGV)`.

Contoh:
Kamu mencoba akses alamat memori kosong atau menulis ke alamat 0, sistem akan menghentikan prosesmu.

`raise(SIGSEGV)` secara manual mengirim sinyal segfault ke diri sendiri.
Tujuannya (di tugas ini) untuk mensimulasikan child process yang mati karena kesalahan serius (bukan karena `exit()` biasa).

**Solusi**

**Video Menjalankan Program**

[video](assets/demo1.mp4)

## Daftar Pustaka

[1] Linux Manual Page for fork(): https://linux.die.net/man/2/fork  
[2] The Open Group Base Specifications Issue 7, IEEE Std 1003.1: https://pubs.opengroup.org/onlinepubs/9699919799/functions/wait.html
