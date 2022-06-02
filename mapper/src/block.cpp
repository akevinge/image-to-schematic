#include "block.hpp"

#include <stdlib.h>

bool trim_block_16x16(block& b) {
    if (b.image.h == 16 && b.image.w == 16) {
        return true;
    }

    u_char* new_img_ptr = static_cast<u_char*>(realloc(b.image.data.get(), b.image.comp * 16 * 16));

    if (new_img_ptr == NULL) {
        return false;
    }

    u_char* old_img_ptr = b.image.data.release();
    b.image.data.reset(new_img_ptr);
    b.image.change_h(16);
    b.image.change_w(16);
    return true;
}