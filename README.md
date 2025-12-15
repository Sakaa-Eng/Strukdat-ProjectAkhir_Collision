# Simulasi Tabrakan Bola 2D  
## Perbandingan Algoritma Brute Force dan Quadtree Menggunakan SFML

---

## Tentang Program

Program ini menggunakan struktur data dari Brute Force serta Quadtree yang digunakan untuk melihat implementasi dari code yang digunakan.

Tujuan utama dari proyek ini adalah **melihat perbandingan antara dua struktur yang ada**, yaitu:

- **Brute Force Collision Detection**
- **Quadtree Spatial Partitioning**

Perbandingan dapa dilakukan dengan melihat **FPS (Frame Per Second)**, mode algoritma aktif, serta jumlah bola yang sedang disimulasikan.

---

## Tools yang digunakan

- **Bahasa Pemrograman:** C++
- **Library Grafis:** SFML 2.6.1+
- **Compiler:** g++ / MinGW / MSVC

---

## Fitur Utama

### 1. Perbandingan Algoritma Deteksi Tabrakan

Program menyediakan dua metode deteksi tabrakan yang dapat diganti saat simulasi berjalan:

- **Brute Force (O(N²))**  
  Metode dasar yang membandingkan setiap bola dengan semua bola lainnya. Implementasinya sederhana dan akurat, namun performanya menurun drastis saat jumlah bola meningkat.

- **Quadtree (≈ O(N log N))**  
  Menggunakan struktur data **Quadtree** untuk membagi ruang simulasi menjadi beberapa area. Bola hanya dicek tabrakannya dengan bola lain yang berada di area yang berdekatan, sehingga performa jauh lebih optimal.

jika ingin mengubah dapat menggunakan **SPASI** untuk berpindah antara mode **Brute Force** dan **Quadtree** secara *real-time*.

---

### 2. Dinamika Bola dan Fisika

- Setiap bola memiliki:
  - Posisi
  - Radius
  - Kecepatan (velocity) acak
- Bola akan:
  - Bergerak bebas di dalam jendela
  - Memantul saat menyentuh dinding
  - Bertumbukan secara elastis dengan bola lain
- Sistem tabrakan :
  - *Positional correction* untuk mencegah bola saling menempel
  - Perhitungan impuls untuk menghasilkan pantulan yang realistis

---

### 3. Interaksi Pengguna (Real-Time Control)

| Input | Fungsi |
|------|-------|
| Klik kiri mouse | Menambahkan 1 bola di posisi kursor |
| A | Menambahkan 50 bola |
| D | Menghapus 50 bola |
| SPASI | Toggle Brute Force / Quadtree |
| S | Mengambil screenshot manual |
| T | Toggle auto-screenshot |
| ESC / Close Window | Keluar dari program |

---

### 4. Tampilan Layar
Di pojok kiri terdapan penjelasan *real-time*:

- Mode deteksi tabrakan yang aktif
- FPS (Frame Per Second)
- Jumlah bola yang sedang disimulasikan
- Petunjuk tombol kontrol

### Kesimpulan

Dari hasil simulasi dapat disimpulkan bahwa:

Brute Force memiliki kompleksitas O(N²) sehingga performanya menurun drastis ketika jumlah bola meningkat.

Quadtree mampu mengurangi jumlah pemeriksaan tabrakan secara signifikan dan menjaga FPS tetap stabil meskipun jumlah bola besar.

Dengan demikian, Quadtree merupakan solusi yang lebih efisien untuk simulasi partikel berskala besar dan aplikasi real-time seperti game dan simulasi fisika.
