/**
 * UTIL convert int to string
 */
/* UTIL unsigned int to hex string */
void util_int_str(unsigned int number, char *buffer, const unsigned int base) {
    const char *digits = "0123456789abcdef";
    char temp[16];
    int counter = 0;
    if (number == 0)
        temp[counter++] = digits[0];
    else
        while (number !=0) {
            temp[counter++] = digits[number % base];
            number /= base;
        }
    counter--;
    while (counter >= 0)
        *(buffer++) = temp[counter--];
    *buffer = '\0';
}
/* UTIL hex string to unsigned int */
unsigned int util_hex_int(const char *buffer) {
    int number = 0;
    int counter = 0;
    while ((counter < 8) && buffer[counter] != 0) {
        number <<= 4;
        if ( (buffer[counter] >= '0') && (buffer[counter] <='9'))
            number += (buffer[counter] - '0');
        else    
        if ((buffer[counter] >= 'a') && (buffer[counter] <='f'))
            number += (buffer[counter] - 0x57);
        counter++;
    }
    
    return number;
}