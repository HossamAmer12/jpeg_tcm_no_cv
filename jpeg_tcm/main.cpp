//
//  main.cpp
//  TCM
//
//  Created by Hossam Amer on 2018-06-27.
//  Copyright © 2018 Hossam Amer. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <math.h>
//#include <ctime>
//#include <cv.h>
//#include <cxcore.h>
//#include <highgui.h>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>


#include "tcm.h"
#include "jpegdecoder.h"

#include "jpegencoder.h"


using namespace std;
//using namespace cv;


#define RUN_DECODER_FULL  0
// Flag for whether this run is for multiple picture or not
#define MULTI_PIC         0
#define IS_ENABLE_ENCODER 1
#define DECODE_SINGLE_PIC  0
#define IS_MAIN_NEW        2
#define RUN_TCM_ANALYSIS_WITHOUT_QF 1


#if IS_MAIN_NEW>1
#include "jpegencoderMultipleQF.h"
#endif

// main new
#if IS_MAIN_NEW

#if IS_MAIN_NEW>1

// (use this main when you want to run parallel from outside with multiple decoding)
int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    if(argc < 4)
    {
        // Tell the user how to run the program
        std::cerr << "Number of arguments should be 3: <input_file_with_full_path> <output_folder> <Quality_factor>" << std::endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    
    /// JPEG Stuff
    //    std::string path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/dataset/";
    
    // Input file:
    std::string filename = argv[1];
    
    // Ouptut folder path:
    std::string enc_path_to_files = argv[2];
    
    // Input quality factor:
    std::string arg = argv[3];
    int quality_factor;
    try {
        std::size_t pos;
        quality_factor = std::stoi(arg, &pos);
        if (pos < arg.size()) {
            std::cerr << "Trailing characters after number: " << arg << '\n';
        }
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << '\n';
        return 1;
    } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << '\n';
        return 1;
    }
    
    // Quality factor experiment:
    ////////////////////////////////////////////////////////
    
    try {
        // Hossam: Save the input fileName
        std::string encoded_filename = filename;
        
        ////// String Processing -- Get the file Name
        size_t found = encoded_filename.find_last_of("/\\");
        std::string filename_first_token = encoded_filename.substr(found+1);
        found = filename_first_token.find_first_of(".");
        std::string filename_second_token = filename_first_token.substr(0, found);
        
        
        
        
        
        // Update the full path for the encoded_file name
        encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
        
        
        // Input params
        //        cout << "Input parameters: " << endl;
        //        cout << "input filename: " << filename << endl;
        //        cout << "output filename: " << encoded_filename << endl;
        //        cout << "quality_factor: " << quality_factor << endl;
        
        // Decode:
//        cout << "Start Decode " << filename << " @ " << quality_factor << endl;
//        jpeg_decoder test(filename);
//        cout << "Done Decode " << filename << " @ " << quality_factor << endl;
//        
//        // Encode:
//        cout << "\nStart Encode " << filename << " @ " << quality_factor << endl;
//        jpeg_encoder enc(&test, encoded_filename, quality_factor);
//        enc.savePicture();
//        cout << "Done Encode; Output is " << encoded_filename << endl;
        
        runEncoderWithMultipleQF(filename, enc_path_to_files);
        
        
//    } catch (exception e) {
    } catch (const std::exception &e) {
        cerr << "Input the folder properly" << endl;
        std::cerr << "My error is: " << e.what() << endl;
        return 1;
        
    }
    
    //    std::vector<string> fileNameArray;
    //    fileNameArray.push_back("frog.JPEG");
    //    fileNameArray.push_back("godonla.JPEG");
    //    fileNameArray.push_back("hawk.JPEG");
    //    fileNameArray.push_back("lizzard.JPEG");
    //    fileNameArray.push_back("mouse.JPEG");
    //    fileNameArray.push_back("owl.JPEG");
    //    fileNameArray.push_back("pepper.jpg");
    //    fileNameArray.push_back("lizzard.JPEG");
    //    fileNameArray.push_back("lizzard.JPEG");
    //    fileNameArray.push_back("phone.JPEG");
    //    fileNameArray.push_back("lion.jpg");
    //    fileNameArray.push_back("river.jpg");
    //
    //    for (std::vector<string>::iterator it = fileNameArray.begin() ; it != fileNameArray.end(); ++it) {
    //
    //
    //        std::string filename = path_to_files + *it;
    //        jpeg_decoder test(filename);
    //        cout << "\n\nDecode " << filename << " is done!" << endl;
    //
    //
    //        // Encoding:
    //        //    std::string encoded_filename = path_to_files + "Lena_encoded.jpg";
    //        //    jpeg_encoder enc(&test, encoded_filename);
    //        //    enc.savePicture();
    //
    //
    //        // Quality factor experiment:
    //        ////////////////////////////////////////////////////////
    //        // Hossam: Save the input fileName
    //        std::string encoded_filename = filename;
    //
    //        ////// String Processing -- Get the file Name
    //        size_t found = encoded_filename.find_last_of("/\\");
    //        std::string filename_first_token = encoded_filename.substr(found+1);
    //        found = filename_first_token.find_first_of(".");
    //        std::string filename_second_token = filename_first_token.substr(0, found);
    //
    //
    //        // for each quality factor
    //        int end_quality_factor = 100;
    //        //        int end_quality_factor = 20;
    //        int quality_factor_step_size = 100;
    //        for (int quality_factor = QFACTOR; quality_factor <= end_quality_factor ; quality_factor += quality_factor_step_size)
    //        {
    //            // Encoded output name
    //            std::string enc_path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/QF_exp/";
    //            encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
    //
    //            cout << "encoded Output: " << encoded_filename << endl;
    //            jpeg_encoder enc(&test, encoded_filename, quality_factor);
    //            enc.savePicture();
    //        } // end for each QualityFactor
    //        
    //    } // end for each fileName
    
    
    
    return 0;
} // end main


#else

// main new2 (use this main when you want to run one picture)
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    
//    
//    if(argc < 4)
//    {
//        // Tell the user how to run the program
//        std::cerr << "Number of arguments should be 3: <input_file_with_full_path> <output_folder> <Quality_factor>" << std::endl;
//        /* "Usage messages" are a conventional way of telling the user
//         * how to run a program if they enter the command incorrectly.
//         */
////        return 1;
//    }
//    
//    /// JPEG Stuff
//    std::string path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/dataset/";
//    
//    // Input file:
////    std::string filename = path_to_files + "Lena.jpg";
////    std::string filename = path_to_files + "lion_write_fast.jpg";
//    std::string filename = path_to_files + "lion_org.jpg";
//    
//    //          std::string filename = path_to_files + "Lena.jpg";
////               std::string filename = path_to_files + "Lena_progressive.jpg";
//    //      std::string filename =  path_to_files + "lena_g.jpg";
//    //      std::string filename =  path_to_files + "lenaV.jpg";
//    //      std::string filename =  path_to_files + "Lena256.jpg";
//    //      std::string filename =  path_to_files + "nature.jpeg";
//    //      std::string filename =  path_to_files + "pepper.jpg";
//    //      std::string filename =  path_to_files + "river.jpg";
//    //		std::string filename =  path_to_files + "tree.jpg";
////    		std::string filename =  path_to_files + "whitewoman.jpg";
//    //      std::string filename =  path_to_files + "baboon.jpg";
//    //      std::string filename =  path_to_files + "Cross.jpeg";
//    //      std::string filename =  path_to_files + "testDown.jpeg";
////          std::string filename =  path_to_files + "Hossam_Amer.jpg";
//    //      std::string filename =  path_to_files + "Yang.jpg";
//    //    std::string filename = path_to_files + "goose_org.jpg";
//    //    		std::string filename = path_to_files + "dog.JPEG";
//    //            std::string filename = path_to_files + "frog.JPEG";
//    //            std::string filename = path_to_files + "godonla.JPEG";
//    //            std::string filename = path_to_files + "goose.jpg";
//    //            std::string filename = path_to_files + "hawk.JPEG";
//    //           std::string filename = path_to_files + "lizzard.JPEG";
////                std::string filename = path_to_files + "mouse.JPEG";
//    //            std::string filename = path_to_files + "owl.JPEG";
//    //            std::string filename = path_to_files + "pepper.jpg";
////                std::string filename = path_to_files + "phone.JPEG";
//    
//    
//    //            std::string filename = path_to_files + "river.jpg";
////                std::string filename = path_to_files + "lion_org.jpg";
//    
//    // Ouptut folder path:
//    std::string enc_path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/dataset/";
//    
//    // Input quality factor:
//    std::string arg = "40";
//    int quality_factor;
//    try {
//        std::size_t pos;
//        quality_factor = std::stoi(arg, &pos);
//        if (pos < arg.size()) {
//            std::cerr << "Trailing characters after number: " << arg << '\n';
//        }
//    } catch (std::invalid_argument const &ex) {
//        std::cerr << "Invalid number: " << arg << '\n';
//        return 1;
//    } catch (std::out_of_range const &ex) {
//        std::cerr << "Number out of range: " << arg << '\n';
//        return 1;
//    }
//    
//    // Quality factor experiment:
//    ////////////////////////////////////////////////////////
//    
//    try {
//        // Hossam: Save the input fileName
//        std::string encoded_filename = filename;
//        
//        ////// String Processing -- Get the file Name
//        size_t found = encoded_filename.find_last_of("/\\");
//        std::string filename_first_token = encoded_filename.substr(found+1);
//        found = filename_first_token.find_first_of(".");
//        std::string filename_second_token = filename_first_token.substr(0, found);
//        
//        
//        // Update the full path for the encoded_file name
//        encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
//        
//        
//        // Decode:
//        cout << "Start Decode " << filename << " @ " << quality_factor << endl;
//        jpeg_decoder test(filename);
//        cout << "Done Decode " << filename << " @ " << quality_factor << endl;
//        
//        // Encode:
//        cout << "\nStart Encode " << filename << " @ " << quality_factor << endl;
//        jpeg_encoder enc(&test, encoded_filename, quality_factor);
//        enc.savePicture();
//        cout << "Done Encode; Output is " << encoded_filename << endl;
//        
//        
//    } catch (Exception e) {
//        cerr << "Input the folder properly" << endl;
//        return 1;
//        
//    }
//    
//    return 0;
//}

//main new2

// (use this main when you want to run parallel from outside with multiple decoding)
int main(int argc, const char * argv[]) {
    // insert code here...
    

    if(argc < 4)
    {
        // Tell the user how to run the program
        std::cerr << "Number of arguments should be 3: <input_file_with_full_path> <output_folder> <Quality_factor>" << std::endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    
    /// JPEG Stuff
//    std::string path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/dataset/";
    
    // Input file:
    std::string filename = argv[1];
    
    // Ouptut folder path:
    std::string enc_path_to_files = argv[2];
    
    // Input quality factor:
    std::string arg = argv[3];
    int quality_factor;
    try {
        std::size_t pos;
        quality_factor = std::stoi(arg, &pos);
        if (pos < arg.size()) {
            std::cerr << "Trailing characters after number: " << arg << '\n';
        }
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << '\n';
        return 1;
    } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << '\n';
        return 1;
    }
    
    // Quality factor experiment:
    ////////////////////////////////////////////////////////
    
    try {
        // Hossam: Save the input fileName
        std::string encoded_filename = filename;
        
        ////// String Processing -- Get the file Name
        size_t found = encoded_filename.find_last_of("/\\");
        std::string filename_first_token = encoded_filename.substr(found+1);
        found = filename_first_token.find_first_of(".");
        std::string filename_second_token = filename_first_token.substr(0, found);
        
        
        // Update the full path for the encoded_file name
#if RUN_TCM_ANALYSIS_WITHOUT_QF
        encoded_filename = enc_path_to_files + filename_second_token + "_TCM" + filename_first_token.substr(found);

#else
        encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
#endif
        
        
        // Input params
//        cout << "Input parameters: " << endl;
//        cout << "input filename: " << filename << endl;
//        cout << "output filename: " << encoded_filename << endl;
//        cout << "quality_factor: " << quality_factor << endl;
        
        // Decode:
        cout << "Start Decode " << filename << " @ " << quality_factor << endl;
        jpeg_decoder test(filename);
        cout << "Done Decode " << filename << " @ " << quality_factor << endl;
        
        // Encode:
        cout << "\nStart Encode " << filename << " @ " << quality_factor << endl;
#if RUN_TCM_ANALYSIS_WITHOUT_QF
         jpeg_encoder enc(&test, encoded_filename);
#else
        jpeg_encoder enc(&test, encoded_filename, quality_factor);
#endif
        enc.savePicture();
        cout << "Done Encode; Output is " << encoded_filename << endl;
        

    } catch (Exception e) {
        cerr << "Input the folder properly" << endl;
        return 1;
        
    }
    
//    std::vector<string> fileNameArray;
//    fileNameArray.push_back("frog.JPEG");
//    fileNameArray.push_back("godonla.JPEG");
//    fileNameArray.push_back("hawk.JPEG");
//    fileNameArray.push_back("lizzard.JPEG");
//    fileNameArray.push_back("mouse.JPEG");
//    fileNameArray.push_back("owl.JPEG");
//    fileNameArray.push_back("pepper.jpg");
//    fileNameArray.push_back("lizzard.JPEG");
//    fileNameArray.push_back("lizzard.JPEG");
//    fileNameArray.push_back("phone.JPEG");
//    fileNameArray.push_back("lion.jpg");
//    fileNameArray.push_back("river.jpg");
//    
//    for (std::vector<string>::iterator it = fileNameArray.begin() ; it != fileNameArray.end(); ++it) {
//        
//        
//        std::string filename = path_to_files + *it;
//        jpeg_decoder test(filename);
//        cout << "\n\nDecode " << filename << " is done!" << endl;
//        
//        
//        // Encoding:
//        //    std::string encoded_filename = path_to_files + "Lena_encoded.jpg";
//        //    jpeg_encoder enc(&test, encoded_filename);
//        //    enc.savePicture();
//        
//        
//        // Quality factor experiment:
//        ////////////////////////////////////////////////////////
//        // Hossam: Save the input fileName
//        std::string encoded_filename = filename;
//        
//        ////// String Processing -- Get the file Name
//        size_t found = encoded_filename.find_last_of("/\\");
//        std::string filename_first_token = encoded_filename.substr(found+1);
//        found = filename_first_token.find_first_of(".");
//        std::string filename_second_token = filename_first_token.substr(0, found);
//        
//        
//        // for each quality factor
//        int end_quality_factor = 100;
//        //        int end_quality_factor = 20;
//        int quality_factor_step_size = 100;
//        for (int quality_factor = QFACTOR; quality_factor <= end_quality_factor ; quality_factor += quality_factor_step_size)
//        {
//            // Encoded output name
//            std::string enc_path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/QF_exp/";
//            encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
//            
//            cout << "encoded Output: " << encoded_filename << endl;
//            jpeg_encoder enc(&test, encoded_filename, quality_factor);
//            enc.savePicture();
//        } // end for each QualityFactor
//        
//    } // end for each fileName
    
    
    
    return 0;
} // end main

#endif // endif for is MAIN = 2

#else


// main old
int main(int argc, const char * argv[]) {
    // insert code here...
    
    /// JPEG Stuff
//    std::string path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/dataset/";
    std::string path_to_files = "/Volumes/DATA/ml/test3/";
    
    
#if DECODE_SINGLE_PIC
    // yes all lena
//          std::string filename = path_to_files + "Lena.jpg";
//            std::string filename = path_to_files + "Lena_progressive.jpg";
    //      std::string filename =  path_to_files + "lena_g.jpg";
    //      std::string filename =  path_to_files + "lenaV.jpg";
    //      std::string filename =  path_to_files + "Lena256.jpg";
    //      std::string filename =  path_to_files + "nature.jpeg";
    //      std::string filename =  path_to_files + "pepper.jpg";
    //      std::string filename =  path_to_files + "river.jpg";
    //		std::string filename =  path_to_files + "tree.jpg";
    //		std::string filename =  path_to_files + "whitewoman.jpg";
    //      std::string filename =  path_to_files + "baboon.jpg";
    //      std::string filename =  path_to_files + "Cross.jpeg";
    //      std::string filename =  path_to_files + "testDown.jpeg";
    //      std::string filename =  path_to_files + "Hossam_Amer.jpg";
    //      std::string filename =  path_to_files + "Yang.jpg";
    //    std::string filename = path_to_files + "goose_org.jpg";
//    		std::string filename = path_to_files + "dog.JPEG";
//            std::string filename = path_to_files + "frog.JPEG";
//            std::string filename = path_to_files + "godonla.JPEG";
//            std::string filename = path_to_files + "goose.jpg";
//            std::string filename = path_to_files + "hawk.JPEG";
//            std::string filename = path_to_files + "lizzard.JPEG";
//            std::string filename = path_to_files + "mouse.JPEG";
//            std::string filename = path_to_files + "owl.JPEG";
//            std::string filename = path_to_files + "pepper.jpg";
//            std::string filename = path_to_files + "phone.JPEG";
    

//            std::string filename = path_to_files + "river.jpg";
//            std::string filename = path_to_files + "Lena.jpg";

//                std::string filename = path_to_files + "n03495258_5610.JPEG";
//            std::string filename = path_to_files + "slowPic.JPEG";
//            std::string filename = path_to_files + "lion_org.jpeg";
    
    
//            std::string filename = path_to_files + "dog-QF-10.JPEG";
    //		std::string filename = path_to_files + "owl.JPEG";
    //		std::string filename = path_to_files + "ILSVRC2012_val_00000878.JPEG";
//    		std::string filename = path_to_files + "lion.jpg";
    
    
    // No:
//            std::string filename =  path_to_files + "test.jpeg";
//        std::string filename =  path_to_files + "mountain.jpg"; // 444 chroma subsampling
//        std::string filename =  path_to_files + "mountainview1.jpg";// 444 chroma subsampling

    // Start time:
    clock_t begin = clock();
    
    
    jpeg_decoder test(filename);
    
    
    //    std::string output_fileName = path_to_files + "myLena.bmp";
    std::string output_fileName = path_to_files + "Hossam_Amer.bmp";
//    std::string output_fileName = path_to_files + "En-hui Yang.bmp";
    
    
#if RUN_DECODER_FULL
    // Remove display
     int output = test.convert_jpg_to_bmp(output_fileName);
    
    
    // End time:
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC);
    cout << "Elapsed Time is: " << elapsed_secs << " seconds." << endl;
    
    // Display Image in OpenCV:
//    if(output) {
//        std::size_t found = output_fileName.find_last_of("/\\");
//        std::string name_file_only = output_fileName.substr(found+1);
//        Mat img = imread(output_fileName, CV_LOAD_IMAGE_COLOR);
//        imshow(name_file_only, img);
//        waitKey(0);
//    }
    
    // Remove display:
    test.display_jpg_yuv("Gray Scale Output", 0);
    
#endif
    
//    test.write_yuv_from_jpg_in_csv(path_to_files + "howy.csv");
//    string pF = path_to_files + "Fankoosh.yuv";
//    test.write_yuv_from_jpg_in_yuv(pF);

#if IS_ENABLE_ENCODER
    // Encoding:
//    std::string encoded_filename = path_to_files + "Lena_encoded.jpg";
//    jpeg_encoder enc(&test, encoded_filename);
//    enc.savePicture();
    
    
    // Quality factor experiment:
    ////////////////////////////////////////////////////////
    // Hossam: Save the input fileName
    std::string encoded_filename = filename;
    
    ////// String Processing -- Get the file Name
    size_t found = encoded_filename.find_last_of("/\\");
    std::string filename_first_token = encoded_filename.substr(found+1);
    found = filename_first_token.find_first_of(".");
    std::string filename_second_token = filename_first_token.substr(0, found);
    

#if RUN_TCM_ANALYSIS_WITHOUT_QF
    cout << "\nStart Encode " << filename << " @ TCM" << endl;
    std::string enc_path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/out_tcm_analysis/";
    encoded_filename = enc_path_to_files + filename_second_token + "_TCM" + filename_first_token.substr(found);
    jpeg_encoder enc(&test, encoded_filename);
    enc.savePicture();
    cout << "Done Encode; Output is " << encoded_filename << endl;
#else
    // for each quality factor
    int end_quality_factor = 100;
    for (int quality_factor = QFACTOR; quality_factor <= end_quality_factor ; quality_factor += 10)
    {
        // Encoded output name
        std::string enc_path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/QF_exp/";
        encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
        
        cout << "encoded Output: " << encoded_filename << endl;
        jpeg_encoder enc(&test, encoded_filename, quality_factor);
        enc.savePicture();
    }
#endif
    
#endif

    
// Decode/Encode multiple pictures with predefined names
#else
    
    std::vector<string> fileNameArray;
//    fileNameArray.push_back("frog.JPEG");
//    fileNameArray.push_back("godonla.JPEG");
//    fileNameArray.push_back("hawk.JPEG");
//    fileNameArray.push_back("lizzard.JPEG");
//    fileNameArray.push_back("mouse.JPEG");
//    fileNameArray.push_back("owl.JPEG");
//    fileNameArray.push_back("pepper.jpg");
//    fileNameArray.push_back("lizzard.JPEG");
//    fileNameArray.push_back("lizzard.JPEG");
//    fileNameArray.push_back("phone.JPEG");
//    fileNameArray.push_back("lion.jpg");
//    fileNameArray.push_back("river.jpg");

    fileNameArray.push_back("n03544143_3251.JPEG");
//    fileNameArray.push_back("test.jpeg");

//    fileNameArray.push_back("lion_org.jpg");
//    fileNameArray.push_back("slowPic.JPEG");
    
    
    for (std::vector<string>::iterator it = fileNameArray.begin() ; it != fileNameArray.end(); ++it) {
        
        
        std::string filename = path_to_files + *it;
        jpeg_decoder test(filename);
        cout << "\n\nDecode " << filename << " is done!" << endl;

        
        
#if IS_ENABLE_ENCODER
        // Encoding:
        //    std::string encoded_filename = path_to_files + "Lena_encoded.jpg";
        //    jpeg_encoder enc(&test, encoded_filename);
        //    enc.savePicture();
        
        
        // Quality factor experiment:
        ////////////////////////////////////////////////////////
        // Hossam: Save the input fileName
        std::string encoded_filename = filename;
        
        ////// String Processing -- Get the file Name
        size_t found = encoded_filename.find_last_of("/\\");
        std::string filename_first_token = encoded_filename.substr(found+1);
        found = filename_first_token.find_first_of(".");
        std::string filename_second_token = filename_first_token.substr(0, found);
        
        
        // for each quality factor
//        int end_quality_factor = 100;
        int end_quality_factor = 100;
        int quality_factor_step_size = 100;
        for (int quality_factor = QFACTOR; quality_factor <= end_quality_factor ; quality_factor += quality_factor_step_size)
        {
            // Encoded output name
//            std::string enc_path_to_files = "/Users/hossam.amer/7aS7aS_Works/work/my_Tools/jpeg_tcm/QF_exp/";
            std::string enc_path_to_files = "/Volumes/DATA/ml/out_test/";
            
            encoded_filename = enc_path_to_files + filename_second_token + "-QF-" + to_string(quality_factor) + filename_first_token.substr(found);
            
            cout << "encoded Output: " << encoded_filename << endl;
            jpeg_encoder enc(&test, encoded_filename, quality_factor);
            enc.savePicture();
        } // end for each QualityFactor

    } // end for each fileName
    
#endif 
    
#endif // end DECODE_SINGLE_PIC
    
//    
//    
//////    cv::Mat img(image_rows,image_cols,image_type,image_uchar,cv::Mat::AUTO_STEP);
//    cv::Mat img2(512,512,CV_8U,ptr2,cv::Mat::AUTO_STEP);
//    imshow("Gray Scale Output", img2);
//    waitKey(0);
    
    cout << "Totally done" << endl;
    
    return 0;
} // end main
#endif
