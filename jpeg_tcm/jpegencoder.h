//
//  jpegencoder.hpp
//  TCM
//
//  Created by Hossam Amer on 2018-08-16.
//  Author: Hossam Amer & Yanbing Jiang, University of Waterloo
//  Copyright © 2018 All rights reserved.
//

#ifndef JPEG_ENCODER_H
#define JPEG_ENCODER_H

#include <stdio.h>
#include <math.h>
#include <fstream>

#include "inttypes.h"
#include "component.h"
#include "huffmantable.h"
#include "jpegdecoder.h"
#include "quantizationtable.h"
#include "TypeDef.h"


class jpeg_encoder {
    
public:
    
    // Quantization tables in case there is no decoded picture
    QuantizationTable quantization_table_write_process_luminance;
    QuantizationTable quantization_table_write_process_chrominance;
    
    // image to export filename
    std::string image_to_export_filename;
    
    int image_to_export_width;
    int image_to_export_height;
    int image_to_export_width_dct;
    int image_to_export_height_dct;
    bool padded_width = false;
    bool padded_height = false;
    
    // NEW to TCM: result array after applying TCM
    vector<double> yc_array;
    vector<int> count_outlier_list, count_outlier_list_sort;
    
    // jpeg decoder
    jpeg_decoder* jpegDecoder;
    
    // Constructor
    jpeg_encoder(std::string filename);
    jpeg_encoder(jpeg_decoder* input_jpeg_decoder, std::string output_filename);
    jpeg_encoder(jpeg_decoder* input_jpeg_decoder, std::string output_filename, int quality_factor);
    bool savePicture();
    
    // For Progressive
    bool progressive_Huff_Format = false; // is progressive_Huff_Format
    vector <HuffmanTable*> default_huffmanTables;
    HuffmanTable* defaultTablesDC[ETF_FORMAT_MAX_COMPONENTS]; // from format.h
    HuffmanTable* defaultTablesAC[ETF_FORMAT_MAX_COMPONENTS];
    
    int counter_FFEX;
    int counter_FFDB = 0;
    
    // quality factor for the encoder (-1 if you don't want to change the table)
    int quality_factor;
    
private:
    
    
    // Various JPEG enums and tables.
    enum { M_SOF0 = 0xC0, M_DHT = 0xC4, M_SOI = 0xD8, M_EOI = 0xD9, M_SOS = 0xDA, M_DQT = 0xDB, M_APP0 = 0xE0 };
    enum { DC_LUM_CODES = 12, AC_LUM_CODES = 256, DC_CHROMA_CODES = 12, AC_CHROMA_CODES = 256, MAX_HUFF_SYMBOLS = 257, MAX_HUFF_CODESIZE = 32,
        EOB_SIGNATURE = -5};
    
    
    // encoder Profiling
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    
    // counter for Y, Cb, Cr blocks
    int count_block_Y, count_block_Cb, count_block_Cr;
    int total_block, total_block_C;
    
    // Changes for Progressive
    void copy_qTables();
    void write_baseline_dct_info(ofstream &file);
    void build_default_huffman_tables();
    
    // DCT functions:
    void perform_dct(vector<vector<double> > &outBlock, int inBlock[8][8]);
    double func_dct(int x, int y, const int block[8][8]);
    float C_dct(int u);
    void DCT2(int ** input, vector<vector<double>> &output);
    void perform_fdct(uint_8 ** image, vector<int> &zigZagArray, int quantizationTable[8][8], int currentComponent = COMPONENT_Y);
    void ZigZagCoding(vector<vector<double> > &block8x8,vector<int>&zigZagArray);
    void ZigZagCoding(double block8x8[8][8], vector<char>&zigZagArray);
    void ZigZagCoding(vector<vector<int> > &block8x8,vector<char>&zigZagArray);
    void ZigZagCoding(int block8x8[8][8], vector<char>&zigZagArray);
    char getCategoryOfDCTCoefficient(int x);
    void writeQuantizationTablesInFile(ofstream &file, vector<char> &table, int tableID);
    
    
    //NEW to TCM perform TCM
    void perform_TCM();
    
    void emit_DQT(ofstream &file);
    
    void writeStartOfFileByteInFile(ofstream &file);
    void writeEOFMarker(ofstream &file);
    void write_default_huffman_tables (ofstream &file);
    
    // My write methods
    void write_jfif_app0(ofstream &file);
    void emit_start_markers(ofstream &file);
    void emit_sof(ofstream &file);
    void emit_sos(ofstream &file);
    
    // copy/paste the header
    uint_8 prev_marker, marker;
    int    num_bytes_in_jpeg_enc_write_buffer;
    
    uint_8 jpeg_enc_write_buffer[JPEG_OUT_HEADER_SIZE + 1];
    void add_byte_to_jpeg_enc_buffer(uint_8 byte, ofstream &file);
    void write_jpeg_enc_buffer(ofstream & file, int numBytes);
    void flush_jpeg_enc_buffer(ofstream & file);
    void writeHeaderFromOriginalPicture(ofstream &file);
    
    
    int parseSegEnc(FILE * fp, ofstream &file);
    // code
    void encodeImageEntryPoint(vector<int> const &luminanceZigZagArray, vector<int> const &chrominanceCbZigZagArray, vector<int> const &chrominanceCrZigZagArray, ofstream &file);
    void encode_mcu(vector<int> const &luminanceZigZagArray, vector<int> const &chrominanceCbZigZagArray, vector<int> const &chrominanceCrZigZagArray, int componentWidth, int componentHeight, int start_x, int start_y, ofstream &file);
    void encode_block(vector<int> const &zigZagArray, int CurrentX, int CurrentY, int currentComponent, int count_block, ofstream &file);
    int returnIndexInZigZagArray(int count_block);
    
    // Clamp our integer between 0 and 255
    inline unsigned char Clamp(int i, int threshold = 255)
    {
        if (i < 0)
            return 0;
        
        // Note: maxSample should normally be 255
        // TODO: threshold should be maxSample (8 bits precision: 2^8-1 or 12 bits precision: 2^12-1)
        else if (i > threshold)
            return 255;
        else
            return i;
    }
    
    
    // JPEG marker generation.
    inline void emit_byte(uint_8 i, ofstream &file)
    {
#if IS_JPEG_ENCODER_WRITE_FAST
        add_byte_to_jpeg_enc_buffer(static_cast<uint_8> (i), file);
#else
        char byte=(char)i;
        file.write((char*)&byte, 1); // 1 character
#endif
    }
    
    inline void emit_word(uint i, ofstream &file)
    {
#if IS_JPEG_ENCODER_WRITE_FAST
        add_byte_to_jpeg_enc_buffer(static_cast<uint_8> (i >> 8), file);
        add_byte_to_jpeg_enc_buffer(static_cast<uint_8> (i & 0xFF), file);
#else
        emit_byte(uint_8(i >> 8), file);
        emit_byte(uint_8(i & 0xFF), file);
#endif
    }
    
    inline void emit_marker(int marker, ofstream &file)
    {
        
#if IS_JPEG_ENCODER_WRITE_FAST
        add_byte_to_jpeg_enc_buffer(0xFF, file);
        add_byte_to_jpeg_enc_buffer(static_cast<uint_8> (marker), file);
#else
        emit_byte(uint_8(0xFF), file);
        emit_byte(uint_8(marker), file);
#endif
    }
    
    // queue length
    unsigned int g_nbits_in_reservoir = 0;
    // the queue of bits
    uint_32 m_bit_buffer = 0;
    //
    unsigned int m_bits_in = 0;
    
    void put_bits(uint bits, uint_32 bits_length, ofstream &file);
    void put_signed_int_bits(int bits, uint_32 bits_length, ofstream &file);
    
    inline static uint bit_count(int temp1)
    {
        if (temp1 < 0) {
            temp1 = -temp1;
        }
        
        uint nbits = 0;
        while (temp1) {
            nbits++;
            temp1 >>= 1;
        }
        return nbits;
    }
    
};


#endif /* JPEG_ENCODER_H */
