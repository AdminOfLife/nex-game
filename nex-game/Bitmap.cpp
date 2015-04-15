#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

#pragma pack(pop)


#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //species height in pixels
    WORD biPlanes; //specifies the number of color planes, must be 1
    WORD biBitCount; //specifies the number of bit per pixel
    DWORD biCompression;//spcifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)



unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr); // small edit. forgot to add the closing bracket at sizeof

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0,imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}



// v2


#include <stdio.h>
#include <strings.h>
#include <sndfile.h>
#include <stdlib.h>
#include <math.h>

#define RATE 44100

typedef struct {
    unsigned short type;                 /* Magic identifier            */
    unsigned int size;                       /* File size in bytes          */
    unsigned int reserved;
    unsigned int offset;                     /* Offset to image data, bytes */
} HEADER;
typedef struct {
    unsigned int size;               /* Header size in bytes      */
    int width,height;                /* Width and height of image */
    unsigned short planes;       /* Number of colour planes   */
    unsigned short bits;         /* Bits per pixel            */
    unsigned int compression;        /* Compression type          */
    unsigned int imagesize;          /* Image size in bytes       */
    int xresolution,yresolution;     /* Pixels per meter          */
    unsigned int ncolours;           /* Number of colours         */
    unsigned int importantcolours;   /* Important colours         */
} INFOHEADER;
typedef struct {
    unsigned char r,g,b,junk;
} COLOURINDEX;


int main(int argc, char *argv[]){
    int i,j,rd;
    int gotindex = 0;
    unsigned char grey,r,g,b;
    double ampl;
    short _2byte[2];
    HEADER header;
    INFOHEADER infoheader;
    COLOURINDEX colourindex[256];
    FILE *fptr; 
    SNDFILE* sndfile = NULL;
    SF_INFO sfinfo;
    long rate = RATE;

    void (*bmpread)();
    void _eightbit(){
        if(fread(&grey, sizeof(unsigned char), 1, fptr) != 1){
        fprintf(stderr,"Image read failed\n");
        exit(-1);
        }
        if (gotindex){
            ampl =  colourindex[grey].r * 64. +
                colourindex[grey].g * 128.+
                colourindex[grey].b * 64.;
        } else {
            ampl = grey * 256. - 32768.;
        }
//      printf("%.2f\n", ampl);
    }
    void _twentyfourbit(){
        do{
            if((rd = fread(&b, sizeof(unsigned char), 1, fptr)) != 1) break;
            if((rd = fread(&g, sizeof(unsigned char), 1, fptr)) != 1) break;
            if((rd = fread(&r, sizeof(unsigned char), 1, fptr)) != 1) break;
        }while(0);
        if(rd != 1){    
            fprintf(stderr,"Image read failed\n");
            exit(-1);
        }
        ampl = r * 64. + g * 128. + b * 64. - 32768.;
//      printf("%.2f\n", ampl);
    }
    if (argc < 3){
        printf("Usage: %s <input.bmp> <output.wav> [samplerate]\n", argv[0]);
        printf("For example:\n\t%s pict.bmp sample.wav 44100 2\n", argv[0]);
        exit(0);
    }
    printf("Input file: %s\n", argv[1]);
    printf("Output file: %s\n", argv[2]);
    if(argc > 3) rate = atoi(argv[3]);
    if(rate < 4000) rate = 4000;
    //if(argc > 4) channels = atoi(argv[4]);        
    sfinfo.samplerate = rate;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV|SF_FORMAT_PCM_16;
    if((fptr = fopen(argv[1],"r")) == NULL) {
        fprintf(stderr,"Unable to open BMP file \"%s\"\n",argv[1]);
        exit(-1);
    }
        /* Read and check BMP header */
    if(fread(&header.type, 2, 1, fptr) != 1){
        fprintf(stderr, "Failed to read BMP header\n");
        exit(-1);
    }
    if(header.type != 'M'*256+'B'){
        fprintf(stderr, "File is not bmp type\n");
        exit(-1);
    }
    do{
        if((rd = fread(&header.size, 4, 1, fptr)) != 1) break;
        printf("File size: %d bytes\n", header.size);
        if((rd = fread(&header.reserved, 4, 1, fptr)) != 1) break;
        if((rd = fread(&header.offset, 4, 1, fptr)) != 1) break;
        printf("Offset to image data is %d bytes\n", header.offset);
    }while(0);
    if(rd =! 1){
        fprintf(stderr, "Error reading file\n");
        exit(-1);
    }
    /* Read and check the information header */
    if (fread(&infoheader, sizeof(INFOHEADER), 1, fptr) != 1) {
        fprintf(stderr,"Failed to read BMP info header\n");
        exit(-1);
    }
    printf("Image size = %d x %d\n", infoheader.width, infoheader.height);
    printf("Number of colour planes is %d\n", infoheader.planes);
    printf("Bits per pixel is %d\n", infoheader.bits);
    printf("Compression type is %d\n", infoheader.compression);
    printf("Number of colours is %d\n", infoheader.ncolours);
    printf("Number of required colours is %d\n", infoheader.importantcolours);
    /* Read the lookup table if there is one */
    for (i=0; i<255; i++){
        colourindex[i].r = rand() % 256;
        colourindex[i].g = rand() % 256;
        colourindex[i].b = rand() % 256;
        colourindex[i].junk = rand() % 256;
    }
    if (infoheader.ncolours > 0) {
        for (i=0; i<infoheader.ncolours; i++){
            do{
            if ((rd = fread(&colourindex[i].b, sizeof(unsigned char),1,fptr)) != 1)
                break;
            if ((rd = fread(&colourindex[i].g, sizeof(unsigned char),1,fptr)) != 1)
                break;
            if ((rd = fread(&colourindex[i].r, sizeof(unsigned char),1,fptr)) != 1)
                break;
            if ((rd = fread(&colourindex[i].junk, sizeof(unsigned char),1,fptr)) != 1)
                break;
            }while(0);
            if(rd != 1){
                fprintf(stderr,"Image read failed\n");
                exit(-1);
            }           
            printf("%3d\t%3d\t%3d\t%3d\n", i,
            colourindex[i].r, colourindex[i].g, colourindex[i].b);
        }
        gotindex = 1;
    }
    if(infoheader.bits < 8){
        printf("Too small image map depth (%d < 8)\n", infoheader.bits);
        exit(-1);
    }
    /* Seek to the start of the image data */
    fseek(fptr, header.offset, SEEK_SET);
    printf("Creating 16bit WAV %liHz.\n", rate);
    sndfile = sf_open(argv[2], SFM_WRITE, &sfinfo);
    if(sndfile == NULL){
        fprintf(stderr, "Cannot open output file!\n"); exit(-1);
    }
    bmpread = _eightbit;
    if(infoheader.bits == 24)
        bmpread = _twentyfourbit;

    /* Read the image */
    for (j=0;j<infoheader.height;j++) {
        _2byte[1] = 32700;
        for (i=0;i<infoheader.width;i++) {
            bmpread();
            _2byte[0] = (short)ampl;
            sf_write_short(sndfile, _2byte, 2);
            _2byte[1] = 0;
        } // i
    } // j
    fclose(fptr);
    sf_close(sndfile);
}
