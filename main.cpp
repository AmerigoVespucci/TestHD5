/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.						     *
 * Copyright by the Board of Trustees of the University of Illinois.	     *
 * All rights reserved.							     *
 *	                                                                     *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have	     *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *  This example illustrates how to write to and read from an existing
 *  dataset. It is used in the HDF5 Tutorial.
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "H5Cpp.h"

#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

//const H5std_string	FILE_NAME("h5tutr_dset.h5");
const H5std_string	FILE_NAME("train.h5");
const H5std_string	DATASET_NAME("data");
const H5std_string	LABELSET_NAME("label");
//const int 	DIM0 = 4;	               // dataset dimensions
//const int 	DIM1 = 6;
const int	DATA_SIZE = 100;                     // dataset dimensions
const int	DATA_DIMS = 2;
const int	LABEL_DIMS = 1;
const int	RANK = 2;

int main (void)
{
    
	// Data initialization.

	int i, j;
	//float data[DATA_SIZE][DATA_DIMS];	    // buffer for data to write
	int NumNums = DATA_SIZE * DATA_DIMS;
	float data[NumNums];
	float labels[DATA_SIZE];

	//for (j = 0; j < DATA_SIZE; j++) {
		for (i = 0; i < NumNums; i++) {
			data[i] = (rand() % 1000) / 1000.0f; // backwards!!!!!
		}
	//}
	for (int l = 0; l < DATA_SIZE; l++) {
		labels[l] = (data[l * 2] > data[(l*2) + 1] ? 1.0f : 0.0f);
	}

    // Try block to detect exceptions raised by any of the calls inside it
    try
    {
		// Turn off the auto-printing when failure occurs so that we can
		// handle the errors appropriately
		//Exception::dontPrint();

		// Open an existing file and dataset.
		//	hid_t file_id = H5Fcreate("test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
		//	herr_t status = H5Fclose(file_id); 
		H5File file(FILE_NAME, H5F_ACC_TRUNC);
		// Create the data space for the dataset.
		hsize_t dims[2];               // dataset dimensions
		dims[1] = DATA_DIMS;
		dims[0] = DATA_SIZE;
		hsize_t label_dims[2];               // dataset dimensions
		label_dims[1] = LABEL_DIMS;
		label_dims[0] = DATA_SIZE;
		DataSpace dataspace(RANK, dims);
		DataSpace labelspace(RANK, label_dims);
		//	DataSet dataset = file.openDataSet(DATASET_NAME);
		// Create the dataset.      
		DataSet dataset = file.createDataSet(DATASET_NAME, PredType::IEEE_F32LE, dataspace);

		// Write the data to the dataset using default memory space, file
		// space, and transfer properties.
		dataset.write(data, PredType::IEEE_F32LE);

		DataSet labelset = file.createDataSet(LABELSET_NAME, PredType::IEEE_F32LE, labelspace);

		labelset.write(labels, PredType::IEEE_F32LE);

    }  // end of try block

    // catch failure caused by the H5File operations
    catch(FileIException error)
    {
		error.printError();
		return -1;
    }

    // catch failure caused by the DataSet operations
    catch(DataSetIException error)
    {
		error.printError();
		return -1;
    }

    return 0;  // successfully terminated
}