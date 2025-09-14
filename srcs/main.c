#include "fdf.h"
#include "libft.h" // ft_putendl_fd için
#include "pars.h"  // get_map_dimensions prototipi burada
#include <stdio.h> // printf için

int	main(int argc, char **argv)
{
	int	total_size;

	// --- Adım 1: Argüman Kontrolü ---
	if (argc != 2)
	{
		return (1);
	}
	// --- Adım 2: Dosya Uzantısı Kontrolü ---
	if (!is_valid_map_file(argv[1]))
	{
		ft_putendl_fd("Hata: Harita dosyasi '.fdf' uzantili olmalidir.", 2);
		return (1);
	}
	// --- Adım 3: Harita Boyutlarını Hesaplama ---
	total_size = get_map_dimensions(argv[1]);
	if (total_size < 0)
	{
		// -1 veya -2 hata kodları içeride zaten perror/mesaj basıyor
		return (1);
	}
	printf("Toplam hücre sayısı (satir × sütun): %d\n", total_size);
	printf("\n--- PARSER TESTI BASARIYLA TAMAMLANDI ---\n");
	return (0);
}
