//==========================================================================
//digitrec.cpp
//==========================================================================
// @brief: A k-nearest-neighbor implementation for digit recognition (k=1)

#include "digitrec.h"

//----------------------------------------------------------
// Top function
//----------------------------------------------------------

void dut(
    hls::stream<bit32_t> &strm_in,
    hls::stream<bit32_t> &strm_out
)
{
  // -----------------------------
  // YOUR CODE GOES HERE
  // -----------------------------
  digit  in_digit;
  bit4_t out_bit4;

  // ------------------------------------------------------
  // Input processing
  // ------------------------------------------------------
  // read the two input 32-bit words (low word first)
  bit32_t input_lo = strm_in.read();
  bit32_t input_hi = strm_in.read();

  // Convert input raw bits to digit 49-bit representation via bit slicing
  in_digit(31, 0) = input_lo;
  in_digit(in_digit.length()-1, 32) = input_hi;

  // ------------------------------------------------------
  // Call digitrec
  // ------------------------------------------------------
  out_bit4 = digitrec( in_digit );

  // ------------------------------------------------------
  // Output processing
  // ------------------------------------------------------

  // Write out the recognized digit (0-9)
  strm_out.write( out_bit4(out_bit4.length()-1, 0) );
}

//----------------------------------------------------------
// Digitrec
//----------------------------------------------------------
// @param[in] : input - the testing instance
// @return : the recognized digit (0~9)

bit4_t digitrec( digit input ) 
{
  #include "training_data.h"

  // This array stores K minimum distances per training set
  bit6_t knn_set[10][K_CONST];

  // Initialize the knn set
  for ( int i = 0; i < 10; ++i )
    for ( int k = 0; k < K_CONST; ++k )
      // Note that the max distance is 49
      knn_set[i][k] = 50; 

  L1800: for ( int i = 0; i < TRAINING_SIZE; ++i ) {
    L10: for ( int j = 0; j < 10; j++ ) {
      // Read a new instance from the training set
      digit training_instance = training_data[j][i];
      // Update the KNN set
      update_knn( input, training_instance, knn_set[j] );
    }
  } 

  // Compute the final output
  return knn_vote( knn_set ); 
}


//-----------------------------------------------------------------------
// update_knn function
//-----------------------------------------------------------------------
// Given the test instance and a (new) training instance, this
// function maintains/updates an array of K minimum
// distances per training set.

// @param[in] : test_inst - the testing instance
// @param[in] : train_inst - the training instance
// @param[in/out] : min_distances[K_CONST] - the array that stores the current
//                  K_CONST minimum distance values per training set

void update_knn( digit test_inst, digit train_inst, bit6_t min_distances[K_CONST] )
{
  // Compute the difference using XOR
  digit diff = test_inst ^ train_inst;

  bit6_t dist = 0;
  // digit mask = 1; // check lsb of diff
  
  // Count the number of set bits
  for ( int i = 0; i < 49; ++i ) { 
    dist += diff[i]; 
    //dist += ((diff>>i) bitand mask);
  }

  // -----------------------------
  // YOUR CODE GOES HERE
  // -----------------------------
  // find the index of maximum distance in min_distances
  bit6_t max = 0;
  int max_ind = 0;

  for (int k = 0; k < K_CONST; k++) {
    if (min_distances[k] > max){
      max = min_distances[k];
      max_ind = k;
    }
  }

  // replace the maximum distance in min_distances if current dist < max
  if (dist < max){
    min_distances[max_ind] = dist;
  }
 
//  for (int i = 0; i < K_CONST; i++)
//    std::cout << "min_dist: " << std::hex << min_distances[i];
//    std::cout << "\n";
}


//-----------------------------------------------------------------------
// knn_vote function
//-----------------------------------------------------------------------
// Given 10xK minimum distance values, this function 
// finds the actual K nearest neighbors and determines the
// final output based on the most common digit represented by 
// these nearest neighbors (i.e., a vote among KNNs). 
//
// @param[in] : knn_set - 10xK_CONST min distance values
// @return : the recognized digit
// 

bit4_t knn_vote( bit6_t knn_set[10][K_CONST] )
{
  // -----------------------------
  // YOUR CODE GOES HERE
  // -----------------------------

  // knn[K_CONST] contains K min distances of knn_set
  bit6_t knn[K_CONST];
  // kdigit[K_CONST] contains K digits corresponding to K min distances of knn_set
  bit4_t kdigit[K_CONST];
  // initialize knn and kdigit
  for (int k = 0; k < K_CONST; k++){
    knn[k] = 50; // default max distance
    kdigit[k] = 0; // default digit 0
  }

  // Search for k min distances of knn_set
  bit6_t dist;
  bit6_t max;
  int max_ind;
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < K_CONST; j++){
      dist = knn_set[i][j];

      // find max_ind -- the index of maximum distance in knn
      // find max     -- the maximum distance in knn
      max = 0;
      max_ind = 0;
      for (int k = 0; k < K_CONST; k++){
        if (knn[k] > max){
          max = knn[k];
          max_ind = k;
        }
      }
    
      // replace the maximum distance in knn if current dist < max
      if (dist < max){
        knn[max_ind] = dist;
        kdigit[max_ind] = i;
      }

    }
  }
 
  // vote for the most common digit in kdigit[K_CONST]
  // vote[10] contains the frequency of each digit
  int vote[10];
  // initialize vote 
  for ( int i = 0; i < 10; i++){
    vote[i] = 0;
  }
  for ( int k = 0; k < K_CONST; k++ ){
    for ( int i = 0; i < 10; i++ ){
      if ( kdigit[k] == i )
        vote[i]++;
    }
  }

//  for (int i = 0; i < 10; i++)
//    std::cout << "vote: " << vote[i];
//  std::cout << "\n";

  // the most common digit
  bit4_t mcdigit;
  int highest = 0;
  for ( int i = 0; i < 10; i++ ){
    if ( vote[i] > highest ){
      highest = vote[i];
      mcdigit = i;
    }
  }
  //std::cout << "digit: " << std::hex << mcdigit;
  
  return mcdigit;

}


