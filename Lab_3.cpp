/* 
 * File:   Lab_3.cpp
 * Author: Alyssa Gibson
 *
 * Created on January 17, 2019, 9:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string speed_calc(string, int, int, int, int);

int main(int argc, char** argv) {
    string plate_num;
    // the plate number of the car
    string h1, m1, h2, m2;
    // temporary variables to store hour and minute variables
    //     before they are converted to integers.
    int hour1, min1, hour2, min2;
    // hour1, min1 = time arrived at the first toll booth
    // hour2, min2 = time arrived at the second toll booth
    ifstream input;
    // File: readings.txt
    ofstream results;
    // File: results.txt
    results.open("results.txt");
    input.open("readings.txt");
    // Open the files needed.
    while (input.eof() == false) {
        // While there is still content in the file,
        // read through it and parse each line with the
        // semicolon delimiter.
        getline(input, plate_num, ';');
        getline(input, h1, ';');
        getline(input, m1, ';');
        getline(input, h2, ';');
        getline(input, m2); // Note: the last one does not need to be
                            //       delimited because it will be
                            //       automatically delimited by /n.
                            // Now that we have individual strings containing just the
                            //     numbers for the times, we can convert them to ints
                            //     using the stoi() function.
        hour1 = stoi(h1);
        min1 = stoi(m1);
        hour2 = stoi(h2);
        min2 = stoi(m2);
        
        // Warning: Kludge alert! <- You said that this Kludge was okay.
        // (In a real life practice, I doubt a Kludge like this would
        //  have any negative consequences, at least.)
        if (!((plate_num == "0" || plate_num == "") && hour1 == min1 == hour2 == min2 && hour1 == 0)) {
            results << speed_calc(plate_num, hour1, min1, hour2, min2) << "\n";
        // Returns immediately if the exit condition (0;0;0;0;0) is met
        }
        
    }
    
    input.close();
    results.close();
    // Close both files so that they save.
    
    return 0;
    
} // End of main method.

string speed_calc (string plate_num, int hour1, int min1, int hour2, int min2) {
    // @params: plate number, time of arrival at each toll booth in 24hr format
    // returns: A string containing whether the driver (identified by plate #)
    //          was speeding or not, and if so how much this person's fine is
    //          depending on how much they were speeding.
    
    const double distance = 14.5;
    // distance between the two will never change, hence constant
    double dif, speed;
    // initialize variables used for speed calculation
    // dif = difference between arrival time 1 and arrival time 2
    // speed = average speed the car was traveling (in mph)
    while (hour1 != hour2) {
        // if the hours are not equal, we require a bit of
        //    calculation before we can determine the 
        //    difference between arrival times
        if (hour1 < hour2) {
            // if the first hour is less than the second
            // ex: 12:40, 13:10
            min2 += 60;
            hour2--;
            // then add 60 to the second minute
            //    and subtract 1 from the hour.
            // ex: 13:10 -> 12:70
        }
        // Originally, I had an else statement determining
        //   what to do when hour2 is smaller than hour1, but
        //   the Lab1 rubric outlines that such a thing shouldn't
        //   happen, since the only way for 24hr time to have that
        //   happen is for it to go to another day.
        else {
            // To prevent an inescapable loop, I decided to 
            //    change it to an error message and return to main.
            return "Invalid times, please try again.";
        }
    }
    // Now that we are sure the hours are equal, we can work with
    //    just minutes for this next part.
    if (min1 > min2) {
        // If the first arrival time's minute value is greater
        //    than the second's
        dif = min1 - min2;
        // Subtract min1 from min2 and assign it to the dif variable
    }
    else {
        // If the second arrival time's minute value is greater
        //    than the first's
        dif = min2 - min1;
        // Subtract min2 from min1 and assign it to the dif variable
    }
    // Below, calculate the speed traveled using the formula provided
    //     in the rubric, then multiply by 60 to get it from miles
    //     per minute to miles per hour.
    speed = ((distance)/(dif))*60;
    
    // Finally, figure out whether the speed traveled exceeds the 
    //     speed limit, 60 mph.
    string result; // Will store the final result of the calculation.
    if (speed < 60) {
        // ISSUE HERE. Tried: - Manually setting compiler to C++14
        //                    - to_string(double); double.str();
        //                    - Unknown whether this compiles on
        //                         Linux or not, can't test.
        // UPDATE: to_string(double) compiled fine with an online converter.
        // https://www.onlinegdb.com/online_c++_compiler#
        // I'm using MinGW on Windows 10.
        result = plate_num + " " + to_string(speed) + " mph. Not speeding.";
    }
    // If they are speeding, calculate the fine based on how much
    //     the driver exceeds the speed limit.
    else {
        // If the program has reached here, this driver was speeding.
        // Now, to determine their fine based on how much they
        // were over the speed limit (60 mph).
        result = plate_num + " " + to_string(speed) + " mph. Speeding. ";
        if (60 < speed && speed <= 70) {
           // If the driver was going faster than 60 mph,
           // but no greater than 70 mph.
           result += "$125";
           // They get fined $125. 
        }
        else if (70 < speed && speed <= 85) {
            // If the driver was going faster than 70 mph,
            // but no greater than 80 mph.
            result += "$275";
            // They get fined $275.
            // (That's like an entire paycheck for me, geez.)
        }
        else {
            // If the driver was in a BIG RUSH.
            result += "$500";
            // They get a BIG FINE.
        }
        
    }
    return result; // Return the result of the calculation as a string
                   //   so main can write it to the results.txt file.
    
}// End speed_calc method. 

