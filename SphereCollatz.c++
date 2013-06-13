// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cin, cout, ios_base, endl, istream, ostream
#include <stack>
#include <algorithm> //max_element

using namespace std;

#define INTERVAL 250 //number of integers that bounds an interval of the meta cache 

using namespace std;

int lazy_cache[1000001] = {0, 1}; //stores the calculated cycle length of any possible number inputed (lazy cache)

int meta_cache[] = { //meta cache storing pre-calculated maximum cycle length of every interval (the value of INTERVAL)
    0, 128, 144, 171, 179, 182, 177, 180, 175, 183, 209, 191, 217, 199, 181, 238, 189, 202, 215, 184, 210, 179, 192, 236, 218, 262, 200, 244, 257, 195, 239, 208, 252, 190, 
    234, 203, 247, 229, 260, 198, 242, 242, 255, 255, 268, 237, 206, 237, 250, 250, 263, 263, 201, 245, 276, 245, 258, 196, 209, 271, 240, 271, 240, 253, 253, 235, 266, 235, 266, 235, 235, 
    279, 248, 248, 230, 261, 261, 199, 212, 274, 274, 243, 243, 212, 256, 256, 256, 207, 269, 269, 269, 269, 238, 238, 251, 282, 251, 251, 251, 264, 264, 264, 246, 233, 233, 202, 277, 308, 
    246, 259, 246, 228, 259, 228, 259, 197, 228, 241, 272, 241, 272, 272, 241, 254, 210, 254, 285, 285, 254, 254, 267, 223, 267, 267, 236, 267, 267, 311, 236, 280, 205, 249, 311, 324, 249, 
    249, 249, 218, 231, 262, 262, 306, 262, 244, 231, 231, 244, 275, 244, 275, 306, 275, 244, 257, 288, 244, 226, 257, 257, 288, 257, 257, 239, 257, 226, 239, 270, 270, 239, 270, 239, 314, 
    239, 239, 239, 252, 283, 252, 252, 283, 314, 283, 252, 252, 252, 265, 296, 234, 265, 296, 265, 234, 265, 234, 278, 265, 309, 203, 247, 278, 203, 340, 278, 309, 322, 247, 247, 247, 260, 
    260, 216, 229, 260, 260, 260, 322, 304, 260, 291, 304, 260, 273, 229, 229, 242, 273, 273, 273, 242, 273, 304, 317, 242, 273, 335, 255, 286, 286, 317, 255, 255, 286, 286, 317, 330, 255, 
    255, 255, 299, 255, 268, 224, 224, 268, 268, 268, 268, 237, 237, 268, 237, 312, 281, 312, 312, 237, 206, 250, 281, 299, 250, 281, 312, 281, 312, 219, 325, 250, 250, 250, 263, 263, 263, 
    294, 294, 232, 294, 263, 294, 263, 325, 307, 263, 263, 294, 307, 219, 307, 232, 351, 214, 245, 245, 276, 307, 201, 338, 307, 276, 276, 307, 320, 289, 276, 276, 320, 258, 214, 289, 245, 
    307, 320, 289, 227, 258, 289, 289, 320, 302, 289, 258, 240, 289, 302, 258, 302, 271, 227, 227, 333, 240, 240, 271, 333, 196, 271, 240, 315, 302, 240, 302, 284, 315, 240, 271, 240, 333, 
    253, 209, 284, 284, 302, 315, 222, 284, 253, 253, 284, 284, 315, 302, 328, 284, 253, 284, 253, 297, 222, 253, 266, 297, 297, 297, 222, 266, 266, 284, 328, 204, 328, 266, 341, 235, 266, 
    235, 297, 279, 310, 235, 266, 310, 310, 235, 235, 204, 248, 248, 279, 297, 310, 248, 341, 248, 310, 279, 354, 310, 279, 323, 292, 248, 279, 248, 279, 248, 261, 217, 292, 261, 292, 310, 
    292, 230, 292, 230, 261, 323, 292, 230, 323, 230, 305, 292, 261, 261, 292, 261, 305, 274, 261, 261, 305, 274, 349, 323, 212, 230, 305, 243, 274, 274, 305, 230, 336, 274, 305, 318, 305, 
    274, 305, 305, 287, 318, 243, 243, 274, 274, 318, 336, 256, 225, 256, 318, 256, 331, 305, 318, 225, 287, 256, 256, 256, 318, 287, 256, 318, 243, 300, 331, 287, 256, 238, 287, 256, 331, 
    331, 225, 287, 300, 269, 344, 300, 300, 331, 225, 300, 238, 269, 287, 331, 300, 207, 331, 269, 313, 313, 300, 269, 256, 238, 300, 344, 313, 282, 238, 269, 313, 269, 313, 331, 313, 207, 
    251, 282, 313, 282, 282, 300, 313, 220, 251, 344, 326, 313, 251, 282, 282, 251, 326, 282, 300, 375, 295, 282, 282, 282, 251, 251, 326, 295, 251, 220, 264, 295, 264, 295, 295, 357, 295, 
    251, 264, 295, 233, 264, 295, 326, 295, 220, 264, 326, 225, 370, 339, 295, 264, 264, 233, 295, 264, 277, 308, 264, 233, 264, 308, 277, 308, 352, 326, 308, 264, 202, 308, 246, 246, 383, 
    295, 308, 308, 233, 277, 339, 246, 246, 321, 308, 277, 277, 352, 308, 277, 290, 370, 290, 277, 246, 277, 277, 290, 277, 321, 339, 259, 246, 246, 290, 321, 259, 290, 334, 308, 290, 321, 
    228, 290, 352, 334, 259, 303, 321, 290, 290, 215, 259, 321, 228, 303, 334, 290, 259, 259, 290, 290, 290, 259, 334, 303, 334, 259, 228, 303, 303, 272, 303, 347, 321, 303, 334, 228, 272, 
    303, 241, 241, 272, 272, 334, 303, 303, 228, 272, 334, 228, 316, 347, 272, 303, 272, 254, 303, 303, 272, 285, 365, 316, 272, 241, 241, 272, 316, 272, 316, 316, 334, 254, 241, 223, 254, 
    316, 285, 254, 285, 329, 303, 223, 316, 316, 285, 285, 347, 223, 329, 316, 285, 316, 316, 285, 223, 254, 316, 254, 360, 329, 298, 285, 254, 254, 241, 329, 285, 329, 329, 347, 342, 329, 
    254, 192, 298, 329, 267, 267, 342, 298, 360, 298, 329, 236, 236, 298, 267, 236, 267, 267, 285, 329, 298, 329, 267, 267, 329, 298, 228, 311, 342, 311, 298, 267, 267, 254, 311, 298, 342, 
    342, 280, 311, 280, 267, 236, 280, 311, 311, 280, 267, 355, 311, 329, 311, 342, 218, 373, 311, 280, 311, 280, 280, 280, 311, 280, 311, 205, 236, 280, 342, 249, 324, 249, 355, 280, 311, 
    311, 280, 355, 324, 311, 280, 218, 298, 373, 293, 280, 280, 249, 280, 280, 280, 280, 324, 386, 231, 342, 262, 324, 249, 249, 262, 324, 262, 262, 293, 337, 200, 355, 293, 324, 231, 249, 
    293, 355, 262, 337, 262, 262, 293, 324, 293, 324, 231, 262, 231, 324, 231, 223, 368, 337, 293, 293, 262, 262, 368, 249, 306, 293, 262, 218, 337, 355, 275, 262, 262, 262, 293, 306, 306, 
    200, 443, 306, 350, 275, 324, 306, 337, 262, 293, 275, 368, 306, 244, 275, 381, 275, 293, 337, 306, 306, 275, 231, 275, 337, 306, 275, 319, 350, 319, 275, 306, 244, 275, 257, 350, 244, 
    306, 275, 213, 293, 368, 288, 244, 275, 244, 275, 275, 319, 275, 288, 319, 319, 319, 337, 257, 244, 244, 275, 244, 257, 319, 288, 257, 257, 288, 332, 306, 350, 319, 319, 257, 244, 288, 
    288, 350, 257, 332, 275, 319, 332, 288, 319, 257, 319, 257, 226, 257, 319, 288, 244, 306, 288, 332, 301, 288, 257, 226, 363, 288, 288, 226, 288, 257, 213, 332, 257, 345, 332, 257, 257, 
    270, 288, 301, 301, 270, 270, 257, 345, 301, 319, 270, 332, 301, 332, 257, 288, 301, 301, 270, 239, 407, 270, 270, 288, 332, 301, 332, 301, 226, 270, 270, 332, 270, 301, 314, 239, 345, 
    314, 270, 301, 270, 270, 252, 257, 345, 239, 314, 345, 345, 416, 363, 345, 283, 270, 252, 270, 239, 270, 314, 283, 283, 283, 314, 358, 314, 332, 252, 314, 345, 221, 252, 252, 314, 314, 
    314, 252, 252, 283, 389, 283, 301, 345, 283, 314, 314, 239, 283, 283, 345, 314, 283, 327, 252, 358, 327, 283, 314, 283, 314, 283, 265, 358, 327, 314, 283, 283, 239, 358, 376, 283, 296, 
    283, 283, 252, 314, 283, 283, 327, 221, 283, 283, 389, 398, 270, 345, 265, 327, 252, 221, 252, 327, 296, 327, 296, 265, 265, 296, 340, 296, 203, 358, 221, 296, 327, 252, 252, 296, 296, 
    358, 265, 234, 265, 265, 327, 265, 296, 327, 296, 265, 327, 265, 234, 265, 371, 327, 296, 221, 234, 371, 296, 340, 309, 265, 296, 265, 296, 265, 252, 340, 234, 327, 296, 340, 221, 340, 
    247, 309, 278, 265, 265, 234, 265, 278, 309, 309, 309, 278, 278, 265, 309, 371, 309, 327, 278, 247, 309, 340, 265, 265, 371, 278, 371, 278, 309, 247, 278, 278, 384, 353, 309, 340, 309, 
    278, 309, 278, 234, 278, 278, 340, 309, 278, 239, 322, 247, 353, 322, 278, 309, 278, 309, 278, 309, 353, 322, 247, 322, 278, 278, 265, 353, 247, 371, 353, 247, 278, 278, 247, 247, 309, 
    278, 322, 322, 291, 291, 278, 322, 384, 229, 340, 291, 260, 322, 247, 247, 247, 216, 291, 322, 322, 322, 260, 260, 229, 291, 353, 291, 309, 353, 291, 291, 322, 260, 229, 247, 291, 291, 
    353, 322, 229, 335, 291, 322, 322, 335, 291, 322, 291, 260, 322, 260, 216, 322, 366, 260, 322, 291, 229, 247, 366, 291, 335, 304, 291, 291, 260, 260, 291, 366, 291, 242, 304, 229, 304, 
    260, 335, 216, 335, 260, 353, 260, 273, 335, 304, 229, 260, 291, 304, 304, 304, 273, 273, 441, 260, 304, 348, 304, 273, 322, 242, 304, 304, 335, 260, 242, 291, 273, 304, 366, 304, 242, 
    242, 273, 273, 379, 348, 304, 335, 304, 304, 335, 304, 273, 229, 229, 273, 348, 335, 304, 379, 273, 379, 242, 348, 317, 304, 273, 304, 273, 242, 273, 379, 304, 348, 348, 242, 317, 273, 
    348, 229, 419, 291, 366, 348, 286, 273, 273, 242, 361, 273, 242, 273, 273, 317, 286, 211, 286, 273, 317, 361, 317, 317, 335, 242, 286, 317, 348, 242, 286, 255, 255, 286, 317, 286, 317, 
    348, 255, 361, 286, 392, 286, 193, 304, 348, 317, 286, 317, 317, 242, 242, 286, 255, 286, 348, 286, 317, 255, 330, 286, 361, 317, 330, 286, 317, 286, 423, 330, 286, 255, 361, 317, 330, 
    255, 317, 286, 361, 286, 361, 304, 379, 330, 299, 286, 255, 286, 374, 255, 255, 361, 317, 286, 330, 299, 224, 299, 286, 330, 211, 330, 273, 348, 343, 268, 330, 255, 255, 255, 255, 268, 
    286, 299, 330, 299, 299, 268, 436, 255, 299, 361, 299, 206, 317, 361, 237, 330, 299, 330, 299, 255, 286, 260, 268, 299, 361, 361, 255, 255, 405, 299, 268, 312, 268, 299, 299, 330, 299, 
    268, 330, 299, 268, 268, 343, 374, 268, 330, 299, 299, 299, 255, 374, 255, 343, 299, 387, 268, 299, 268, 268, 237, 268, 250, 255, 237, 343, 237, 330, 312, 299, 343, 224, 414, 281, 237, 
    361, 343, 281, 343, 268, 250, 268, 268, 281, 299, 312, 312, 312, 206, 281, 281, 449, 312, 312, 374, 312, 219, 330, 237, 250, 312, 312, 343, 219, 268, 374, 312, 281, 312, 374, 281, 312, 
    250, 250, 281, 281, 387, 343, 281, 312, 343, 281, 312, 281, 343, 312, 281, 219, 237, 281, 281, 343, 281, 312, 312, 268, 325, 281, 281, 356, 325, 325, 281, 312, 250, 418, 312, 281, 281, 
    312, 356, 312, 325, 356, 312, 281, 281, 356, 237, 356, 299, 237, 374, 281, 294, 281, 281, 281, 250, 250, 281, 312, 281, 237, 281, 325, 219, 312, 343, 281, 325, 387, 396, 268, 250, 343, 
    250, 338, 250, 325, 356, 250, 232, 250, 281, 325, 294, 325, 294, 387, 325, 263, 263, 294, 294, 400, 294, 294, 325, 312, 356, 232, 294, 294, 325, 263, 232, 263, 294, 294, 294, 356, 294, 
    325, 232, 250, 338, 281, 263, 325, 325, 338, 294, 294, 325, 294, 263, 325, 294, 263, 263, 232, 325, 263, 369, 338, 325, 263, 369, 294, 250, 369, 263, 387, 338, 307, 294, 276, 294, 263, 
    276, 232, 294, 369, 294, 294, 294, 338, 338, 325, 307, 263, 263, 338, 219, 338, 281, 245, 356, 263, 276, 263, 338, 263, 307, 263, 263, 276, 294, 307, 280, 307, 307, 201, 276, 276, 444, 
    263, 307, 369, 307, 307, 276, 325, 232, 245, 307, 307, 338, 338, 263, 245, 369, 307, 276, 307, 369, 307, 369, 307, 294, 413, 276, 276, 382, 276, 351, 294, 307, 338, 307, 307, 276, 276, 
    307, 276, 232, 232, 276, 276, 276, 338, 338, 307, 307, 294, 276, 382, 245, 245, 351, 307, 320, 276, 276, 307, 276, 276, 307, 276, 382, 307, 263, 351, 351, 245, 338, 320, 276, 276, 351, 
    263, 422, 294, 245, 369, 320, 351, 382, 351, 245, 276, 258, 258, 245, 289, 307, 276, 232, 320, 320, 320, 214, 289, 338, 276, 320, 320, 382, 391, 227, 289, 338, 382, 258, 320, 320, 320, 
    351, 245, 276, 258, 320, 320, 320, 320, 320, 320, 320, 258, 276, 426, 245, 320, 289, 395, 289, 289, 307, 289, 351, 320, 289, 320, 320, 320, 289, 227, 258, 245, 289, 258, 289, 351, 320, 
    289, 245, 276, 333, 395, 289, 320, 364, 333, 289, 320, 289, 320, 289, 426, 258, 320, 289, 271, 258, 258, 320, 333, 364, 258, 320, 289, 289, 364, 245, 245, 364, 271, 382, 333, 289, 302, 
    364, 258, 333, 258, 377, 302, 289, 258, 364, 289, 227, 289, 333, 302, 320, 302, 470, 289, 258, 333, 214, 333, 276, 258, 351, 346, 258, 364, 333, 395, 258, 302, 258, 227, 271, 289, 302, 
    302, 333, 333, 302, 302, 271, 271, 439, 258, 258, 302, 364, 302, 302, 333, 320, 364, 227, 333, 302, 302, 271, 333, 302, 258, 271, 289, 302, 271, 302, 364, 302, 271, 364, 408, 258, 408, 
    302, 302, 333, 377, 271, 346, 302, 302, 333, 302, 377, 271, 333, 302, 271, 271, 227, 333, 346, 271, 346, 271, 333, 302, 302, 377, 240, 271, 377, 320, 240, 346, 284, 315, 302, 284, 271, 
    302, 271, 271, 333, 302, 271, 377, 302, 258, 346, 346, 240, 240, 333, 315, 271, 271, 346, 227, 346, 417, 289, 253, 364, 346, 271, 284, 271, 346, 271, 315, 302, 359, 271, 284, 302, 315, 
    271, 315, 315, 346, 284, 284, 284, 452, 271, 240, 315, 377, 359, 315, 315, 284, 333, 240, 253, 284, 315, 302, 346, 346, 271, 284, 253, 377, 315, 284, 315, 315, 284, 315, 315, 346, 253, 
    421, 359, 284, 284, 390, 328, 359, 284, 315, 315, 346, 271, 315, 284, 284, 315, 315, 284, 240, 253, 240, 284, 253, 284, 284, 359, 346, 284, 315, 253, 271, 328, 284, 284, 315, 359, 315, 
    328, 284, 284, 315, 284, 284, 421, 328, 315, 284, 284, 266, 253, 359, 359, 328, 359, 346, 315, 284, 315, 284, 359, 271, 253, 359, 302, 253, 377, 266, 284, 297, 284, 359, 284, 284, 266, 
    372, 297, 284, 315, 359, 328, 315, 284, 328, 297, 328, 315, 297, 346, 284, 253, 328, 390, 399, 328, 271, 253, 346, 341, 253, 315, 359, 328, 328, 253, 222, 253, 253, 266, 266, 328, 297, 
    297, 328, 297, 328, 297, 328, 266, 266, 434, 372, 297, 297, 359, 297, 359, 204, 328, 315, 359, 235, 328, 297, 297, 284, 328, 297, 297, 315, 266, 297, 297, 284, 297, 297, 359, 328, 359, 
    328, 235, 284, 403, 284, 297, 266, 328, 328, 328, 266, 297, 297, 328, 297, 297, 266, 266, 328, 297, 279, 372, 266, 266, 328, 341, 372, 266, 266, 341, 297, 297, 297, 372, 253, 235, 372, 
    235, 279, 297, 341, 403, 385, 372, 279, 248, 297, 266, 266, 279, 297, 266, 372, 248, 297, 235, 248, 341, 310, 235, 328, 310, 297, 297, 266, 341, 341, 222, 412, 341, 266, 248, 359, 341, 
    266, 279, 341, 341, 235, 341, 310, 354, 266, 266, 279, 297, 310, 310, 266, 310, 310, 279, 310, 279, 279, 279, 447, 235, 310, 310, 372, 354, 310, 310, 217, 328, 323, 372, 248, 248, 310, 
    310, 310, 341, 204, 266, 248, 266, 372, 310, 279, 279, 310, 372, 310, 279, 310, 310, 248, 310, 354, 279, 279, 341, 385, 279, 354, 279, 310, 310, 341, 374, 310, 310, 279, 310, 341, 310, 
    279, 235, 235, 235, 235, 279, 266, 279, 279, 341, 310, 310, 310, 279, 266, 279, 385, 328, 279, 279, 354, 248, 323, 323, 310, 292, 248, 310, 279, 279, 416, 310, 248, 279, 279, 310, 310, 
    354, 310, 354, 248, 354, 341, 323, 279, 279, 279, 354, 354, 266, 425, 354, 261, 248, 372, 323, 416, 292, 279, 354, 248, 279, 279, 261, 261, 248, 279, 230, 310, 248, 279, 310, 323, 323, 
    323, 292, 217, 310, 292, 341, 279, 248, 323, 323, 385, 394, 323, 323, 230, 341, 336, 292, 261, 336, 323, 323, 310, 354, 354, 279, 336, 248, 385, 310, 323, 292, 265, 323, 323, 323, 323, 
    385, 354, 295, 261, 429, 230, 323, 292, 354, 398, 354, 292, 323, 305, 310, 354, 217, 292, 323, 292, 279, 292, 323, 292, 292, 230, 261, 248, 292, 292, 261, 292, 292, 367, 292, 323, 292, 
    318, 279, 248, 398, 323, 292, 261, 323, 305, 367, 336, 292, 292, 292, 323, 292, 292, 292, 261, 261, 323, 292, 230, 323, 323, 261, 323, 323, 336, 367, 261, 261, 336, 305, 292, 292, 367, 
    292, 248, 230, 367, 310, 248, 385, 336, 292, 292, 305, 292, 274, 261, 336, 261, 261, 380, 230, 292, 261, 261, 367, 336, 323, 336, 336, 336, 305, 336, 323, 305, 305, 305, 261, 261, 336, 
    230, 380, 336, 336, 261, 261, 354, 349, 261, 261, 274, 261, 336, 398, 261, 367, 261, 390, 261, 261, 274, 292, 336, 305, 305, 336, 336, 305, 336, 336, 199, 274, 274, 442, 261, 305, 305, 
    323, 367, 349, 305, 305, 212, 274, 323, 367, 274, 243, 336, 305, 305, 305, 336, 336, 305, 318, 243, 261, 367, 305, 305, 274, 305, 305, 367, 305, 336, 367, 305, 243, 305, 261, 411, 274, 
    274, 274, 380, 336, 336, 349, 305, 305, 305, 336, 369, 305, 380, 274, 274, 336, 305, 305, 274, 274, 230, 274, 274, 349, 274, 261, 349, 274, 336, 305, 305, 305, 305, 380, 292, 274, 380, 
    323, 274, 243, 305, 349, 411, 318, 274, 305, 380, 274, 305, 274, 274, 274, 274, 305, 305, 274, 380, 256, 336, 305, 349, 305, 349, 318, 243, 336, 318, 318, 274, 305, 274, 349, 230, 261, 
    420, 349, 292, 274, 230, 367, 318, 411, 367, 380, 274, 349, 256, 274, 243, 256, 362, 243, 243, 287, 243, 305, 310, 318, 274, 349, 318, 318, 287, 318, 212, 287, 287, 362, 287, 243, 318, 
    318, 380, 362, 389, 243, 318, 225, 336, 331, 380, 349, 256, 287, 318, 243, 305, 349, 349, 287, 287, 243, 243, 380, 424, 318, 287, 318, 318, 318, 287, 380, 287, 318, 349, 256, 274, 424, 
    424, 287, 318, 287, 349, 393, 349, 362, 318, 318, 305, 318, 349, 212, 287, 318, 287, 287, 318, 318, 318, 287, 300, 243, 256, 243, 349, 287, 256, 287, 287, 287, 349, 349, 362, 287, 318, 
    243, 274, 274, 393, 393, 287, 287, 318, 362, 300, 318, 331, 318, 318, 287, 274, 318, 287, 305, 424, 256, 331, 318, 287, 287, 256, 318, 318, 362, 318, 362, 331, 362, 256, 349, 331, 331, 
    318, 287, 287, 362, 362, 243, 256, 362, 305, 287, 256, 380, 331, 269, 287, 300, 287, 362, 256, 243, 331, 256, 269, 375, 269, 300, 287, 256, 362, 300, 287, 318, 331, 287, 331, 300, 300, 
    225, 318, 225, 300, 468, 300, 256, 256, 331, 287, 393, 402, 331, 331, 256, 238, 349, 344, 256, 256, 269, 362, 331, 256, 393, 362, 300, 256, 331, 225, 256, 331, 207, 437, 331, 300, 256, 
    331, 331, 300, 300, 300, 393, 269, 269, 269, 437, 256, 300, 331, 300, 362, 362, 344, 356, 300, 207, 331, 318, 269, 362, 225, 287, 331, 300, 300, 300, 331, 331, 269, 300, 313, 238, 300, 
    287, 375, 300, 269, 300, 300, 300, 362, 300, 331, 362, 269, 406, 300, 256, 300, 406, 300, 300, 287, 331, 375, 313, 269, 344, 300, 331, 300, 282, 437, 300, 300, 375, 269, 269, 331, 300, 
    300, 282, 282, 331, 225, 269, 468, 344, 331, 375, 344, 269, 344, 331, 300, 300, 300, 300, 375, 256, 256, 375, 375, 318, 269, 282, 393, 344, 282, 406, 313, 388, 282, 282, 251, 300, 269, 
    269, 269, 331, 313, 300, 251, 331, 375, 313, 300, 300, 238, 344, 344, 406, 238, 238, 238, 331, 313, 313, 300, 269, 300, 344, 238, 406, 388, 415, 287, 251, 238, 251, 362, 357, 344, 269, 
    362, 375, 269, 344, 238, 269, 313, 251, 300, 357, 238, 344, 282, 238, 344, 313, 313, 269, 344, 313, 313, 344, 313, 450, 300, 282, 282, 357, 450, 238, 313, 313, 313, 313, 375, 313, 369, 
    313, 238, 331, 331, 326, 375, 282, 251, 326, 313, 313, 313, 313, 344, 344, 282, 313, 282, 251, 282, 375, 419, 313, 282, 274, 313, 313, 375, 282, 375, 344, 313, 344, 251, 251, 419, 274, 
    357, 282, 282, 282, 344, 388, 313, 344, 357, 329, 313, 313, 295, 344, 207, 295, 313, 282, 282, 313, 282, 344, 313, 251, 282, 525, 238, 282, 344, 269, 282, 269, 388, 282, 282, 357, 282, 
    344, 313, 282, 313, 238, 269, 269, 282, 388, 331, 282, 251, 282, 357, 295, 357, 326, 401, 282, 313, 282, 220, 313, 282, 264, 282, 419, 326, 313, 251, 282, 282, 313, 313, 313, 207, 357, 
    313, 357, 326, 357, 357, 344, 344, 326, 326, 313, 282, 313, 357, 357, 269, 238, 428, 357, 300, 264, 251, 264, 388, 326, 357, 282, 375, 282, 282, 357, 282, 282, 282, 264, 251, 370, 251, 
    295, 295, 233, 313, 357, 282, 326, 313, 220, 326, 326, 326, 295, 326, 220, 313, 295, 295, 344, 295, 251, 326, 326, 326, 388, 370, 397, 326, 326, 251, 233, 344, 339, 326, 251, 313, 339, 
    357, 326, 326, 388, 326, 357, 295, 326, 282, 295, 264, 282, 264, 432, 326, 295, 326, 295, 326, 326, 326, 326, 326, 388, 326, 357, 264, 264, 432, 264, 370, 295, 326, 295, 357, 401, 357, 
    357, 295, 202, 326, 308, 326, 264, 357, 344, 295, 326, 295, 295, 282, 295, 326, 326, 264, 295, 251, 313, 264, 251, 282, 370, 295, 282, 295, 295, 295, 370, 295, 326, 326, 357, 295, 401, 
    233, 282, 282, 401, 282, 295, 264, 264, 326, 370, 326, 370, 339, 264, 295, 326, 295, 277, 326, 295, 295, 295, 264, 264, 264, 326, 295, 295, 277, 295, 370, 264, 233, 264, 326, 326, 339, 
    264, 370, 251, 264, 339, 326, 295, 339, 295, 295, 370, 295, 251, 251, 233, 370, 313, 401, 233, 277, 388, 339, 401, 295, 308, 383, 370, 277, 264, 251, 295, 264, 246, 339, 383, 264, 233, 
    295, 264, 417, 370, 246, 339, 326, 295, 295, 233, 339, 370, 308, 339, 308, 326, 308, 295, 476, 308, 264, 295, 339, 339, 233, 383, 410, 339, 401, 246, 264, 246, 357, 352, 339, 264, 277, 
    370, 277, 339, 339, 233, 264, 339, 308, 264, 393, 264, 233, 339, 277, 277, 295, 339, 308, 339, 295, 432, 339, 308, 339, 308, 308, 339, 277, 277, 277, 277, 445, 383, 308, 264, 308, 308, 
    370, 352, 308, 364, 308, 215, 339, 277, 326, 321, 370, 233, 476, 339, 277, 308, 383, 295, 308, 339, 339, 202, 308, 339, 326, 264, 264, 370, 246, 308, 277, 277, 277, 308, 308, 370, 277, 
    339, 339, 370, 308, 414, 295, 308, 269, 414, 233, 277, 321, 277, 339, 383, 339, 277, 430, 352, 445, 308, 295, 308, 295, 372, 277, 308, 308, 383, 277, 277, 339, 339, 308, 308, 277, 277, 
    339, 233, 277, 233, 339, 352, 277, 383, 277, 352, 277, 352, 339, 308, 352, 308, 383, 308, 383, 295, 264, 277, 383, 264, 326, 277, 277, 246, 352, 290, 308, 308, 321, 414, 308, 383, 308, 
    246, 308, 414, 277, 277, 277, 414, 246, 308, 246, 277, 277, 383, 308, 308, 339, 308, 352, 308, 352, 321, 321, 352, 264, 339, 246, 321, 321, 308, 277, 277, 308, 352, 352, 264, 233, 423, 
    352, 295, 290, 246, 259, 370, 383, 277, 414, 277, 290, 383, 277, 352, 259, 228, 277, 277, 321, 246, 365, 277, 308, 277, 308, 228, 246, 308, 321, 321, 308, 277, 352, 277, 321, 321, 290, 
    321, 458, 308, 352, 290, 290, 339, 277, 246, 277, 321, 321, 321, 383, 365, 392, 321, 321, 334, 391, 290, 339, 334, 246, 383, 246, 259, 334, 321, 321, 246, 383, 321, 352, 352, 321, 321, 
    334, 246, 246, 259, 383, 427, 321, 290, 290, 321, 321, 321, 383, 321, 383, 321, 290, 383, 352, 259, 293, 321, 427, 290, 365, 290, 321, 290, 290, 352, 396, 352, 352, 290, 290, 321, 308, 
    308, 321, 290, 352, 215, 290, 321, 321, 290, 290, 321, 290, 321, 321, 259, 290, 352, 290, 246, 259, 246, 290, 365, 290, 277, 290, 259, 290, 365, 365, 290, 352, 321, 352, 321, 321, 316, 
    277, 277, 246, 396, 321, 396, 290, 259 
};

//function prototypes
bool collatz_read (std::istream&, int&, int&);
int collatz_eval (int, int);
void collatz_print (std::ostream&, int, int, int);
void collatz_solve (std::istream&, std::ostream&);
int cycle_length(unsigned int);

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    assert(i <= 1000000);
    assert(j <= 1000000);
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    assert(i <= 1000000);
    assert(j <= 1000000);
    
    int v = 1;
    int len; //holding the result for each invocation of cycle_length
    unsigned int x, y; //for adjusting i and j (smaller one to x and bigger one to y)

    //find which one is upper bound and lower bound
    if(i > j)
    {
        x = j;
        y = i;
    }
    else
    {
       y = j;
       x = i;
    }

    while(x % INTERVAL && x <= y) //examine numbers below the lower bound of the meta cache
    {
        if((len = cycle_length(x++)) > v)
        {
            v = len;
        } 
    }

    //
    int lower_bound = x / INTERVAL; //index to the lower bound of the meta cache
    while((x < y) && (y - x >= INTERVAL)) ///examine numbers in the meta cache
    {
        x += INTERVAL;
    }
    int upper_bound = x / INTERVAL; //index to the upper bound of the meta cache (get the maximum cycle length in the meta cache within the given boundry)
    if((upper_bound - lower_bound > 1) && ((len = *max_element(meta_cache + lower_bound , meta_cache + upper_bound)) > v))
    {
        v = len;
    }

    for(; x <= y; x++) //examine numbers above the lower bound of the meta cache
    {
        if((len = cycle_length(x)) > v)
        {
            v = len;
        }
    }

    assert(v > 0);
    return v;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(i <= 1000000);
    assert(j <= 1000000);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {

    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

//----------
//cycle_length
//----------

int cycle_length(unsigned int x)
{

    assert(x <= 1000000);

    stack<int> numbers; //stores any numbers that are on the path of finding the cycle length
    int len;
    bool done = false; //check if a calculated cycle length in lazy cache is found

    numbers.push(x);
    while(!done)
    {
        if(x <= 1000000 && x > 0 && lazy_cache[x]) //check if out of the range of lazy cache
        {
            done = true;
            len = lazy_cache[x];
        }
        else
        {
            x = (x % 2) ? (x + (x << 1) + 1) : (x >> 1);
            numbers.push(x);
        }
    }

    //fill the lazy cache
    while(numbers.size() != 1)
    {
        if(numbers.top() <= 1000000 && numbers.top() > 0) //check if out of the range of lazy cache
        {
            lazy_cache[numbers.top()] = len;
        }
        numbers.pop();
        len++;
    }

    lazy_cache[numbers.top()] = len;
    return len;
} 


// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}

