struct BCD_format{
    int bits[4];
};

void offset_BCD_left(struct BCD_format *val);
void check_and_convert_bit(struct BCD_format* val);

//установка полубайта в определеную позицию
void set_four_bit(int *n, int bit, int pos_quadro);

void set_four_bit(int *n, int bit, int pos_quadro);