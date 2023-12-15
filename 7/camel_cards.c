#include <stdio.h>
#include <stdlib.h>

enum CardType {
  HIGH = 0,
  ONE = 1,
  TWO = 2,
  THREE = 3,
  FULL = 4,
  FOUR = 5,
  FIVE = 6,
};

typedef struct {
  unsigned int data; // Only use 20 bit of these
  unsigned int bid;
  CardType type;
} CardSet;


unsigned int data_from_arr(const char arr[5]);
CardType rate_card(const char arr[5]);
void quick_sort(CardSet arr[], int low, int high);


int main (int argc, char *argv[]) {
  FILE* file;
  file = fopen("./input.txt", "r");

  fseek(file, 0, SEEK_END);

  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* buffer = (char *)malloc(file_size + 1);

  fread(buffer, 1, file_size, file);
  fclose(file);


  const size_t set_len = 1000;
  CardSet sets[set_len];
  for (size_t i = 0; i < set_len; ++i) {
    char card_buf[5];
    char* card_iter = card_buf;

    while (*buffer != ' ') {
      *card_iter = *buffer;
      card_iter++;
      buffer++;
    }
    buffer++;

    char bid_buf[5];
    for (size_t i = 0; i < 4; ++i) {
      bid_buf[i] = 0;
    }
    bid_buf[4] = '\0';

    char* bid_iter = bid_buf;
    char* bid_start_addr = bid_iter;

    while (*buffer != '\n') {
      *bid_iter = *buffer;
      bid_iter++;
      buffer++;
    }

    buffer++;
    CardSet card_set;

    card_set.bid = atoi(bid_buf);
    card_set.data = data_from_arr(card_buf);
    card_set.type = rate_card(card_buf);
    sets[i] = card_set;
  }


  quick_sort(sets, 0, set_len - 1);
  unsigned int res = 0;
  for (size_t i = 0; i < set_len; ++i) {
    printf("%d: %d\n", i + 1, sets[i].bid);
    res += sets[i].bid * (i + 1);
  }
  printf("%ld", res);

  return 0;
}


CardType rate_card(const char arr[5]) {
  unsigned char found_char = 0;
  unsigned char found_vals[2];

  unsigned char* found_vals_iter = found_vals;

  for (size_t i = 0; i < 5; ++i) {
    if (arr[i] == found_char) continue;
    size_t count = 0;
    for (size_t y = 0; y < 5; ++y) {
      if (arr[i] == arr[y]) {
        count++;
      }
    }
    if (count == 1) continue;
    *found_vals_iter = count;
    found_vals_iter++;

    if (found_char != 0) break;

    found_char = arr[i];
  }

  if (found_vals[0] == 0 && found_vals[1] == 0) {
    return CardType::HIGH;
  }

  switch (found_vals[0] ^ found_vals[1]) {
    case 5: return CardType::FIVE;
    case 4: return CardType::FOUR;
    case 1: return CardType::FULL;
    case 3: return CardType::THREE;
    case 0: return CardType::TWO;
    case 2: return CardType::ONE;
  }
  return CardType::HIGH;
}

unsigned int data_from_arr(const char arr[5]) {
  unsigned int res = 0;

  for (size_t i = 0; i < 5; ++i) {
    unsigned int current = arr[i];
    unsigned int char_val = 0;

    if (current >= 0x32 && current <= 0x39) {
      char_val = current - 0x32;
    } else {
      switch (current) {
        case 'T': char_val = 8; break;
        case 'J': char_val = 9; break;
        case 'Q': char_val = 10; break;
        case 'K': char_val = 11; break;
        case 'A': char_val = 12; break;
      }
    }
    if (char_val == 0) { printf("Nothin matched with: %d \n", current); }
    res <<= 4;
    res |= char_val;

  }
  return res;
}


int partition(CardSet arr[], int low, int high)
{
  CardSet pivot = arr[high];
  int i = low - 1;
   
  for(size_t j = low; j <= high; ++j)
  {
    if(arr[j].type < pivot.type || (arr[j].type == pivot.type && arr[j].data < pivot.data))
    {
      ++i;
      CardSet tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
    }
  }
  CardSet tmp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = tmp;

  return i + 1;
}
 
void quick_sort(CardSet arr[], int low, int high)
{
  if(low < high)
  {
    int pi = partition(arr, low, high);
     
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}
