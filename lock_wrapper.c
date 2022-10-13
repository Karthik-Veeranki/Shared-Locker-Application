/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////			***	CS 222 ***	        		/////////////////////////////////
///////////////////////			SHARED LOCKER APPLICATION		/////////////////////////////////

/*__________ Author            :  Siddhi Venkata Sai Karthik Veeranki   __________*/
/*__________ Branch    			   :  Mathematics and Computing      __________*/
/*__________ Roll number		   :  2003325      __________*/

/////////////////////////////////////////////////////////////////////////////////////////



// including the necessary header files
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>



int global_counter = 0;		// a global variable to keep track of total number of entries into the file 'config.txt'

int deleted_line_number_array[100];		// an array to keep track of those lockers (here the line number) that are been entered to get deleted
int index_of_deleted_line_number_array = 0;		// a global variable to keep track of the size of above array


// listing all the functions present in this program. Detailed descrption is given at the start of each function.

bool isPrime(int n);
void open_empty_file();
void add_locker_entry();
void delete_locker_entry();
void use();
void configure();
int euclidian_gcd(int a, int b, int *x, int *y);




/*
The following function isPrime() takes one parameter 'n' as input:
	n - an integer to check if it is prime number or not
	
The function returns either true or false:
	-> true, if n is prime 
	-> false, if n is not prime
Hence the return type is bool.
*/

bool isPrime(int n)
{
	if(n == 1)		// if n = 1, it return false, since 1 is not prime
		return false;
		
	if(n == 2 || n == 3)	// if n = 2 or n = 3, function returns true, since 2 and 3 both are prime numbers 
		return true;
		
	if(n % 2 == 0 || n % 3 == 0)	// we check if n is divisible by 2 or 3, and returns false if divisible
		return false;
	
	for(int i = 5;i*i <= n;i = i + 6)	// if n doesnot fall under any of the above base cases, then we iterate through following loop
	{
		if(n % i == 0 || n % (i+2) == 0)
			return false;
	}
	return true;
}



/*
The following function open_empty_file() takes no parameter as input.	
The function opens the file config.txt in write mode and makes the contents of the file empty.
It returns nothing, hence the return type is void.
*/


void open_empty_file()
{
	FILE*fp;
	fp = fopen("config.txt","w");
	
	if(fp == NULL)				// if the config.txt file fails to open then we terminate the program by printing apt message
	{
		printf("\nFile read error\n");
		exit(0);
	}
	
	fprintf(fp,"");
	fclose(fp);
	return;
}



/*
The following function add_locker_entry() takes no parameter as input.
	
As the name suggests, the function asks the user to enter the following three parameters one by one.
	-> locker_id - a string composed of atmost 5 characters
	-> k - an integer to store the number of users
	-> L - a 10-digit long integer to store the unique locker key for this given locker_id

The function does the following major tasks:
	-> prints the entries (locker_id,k,p1,....,pk) into the file config.txt as in required format. Here p1,...,pk are k prime numbers generated.
	-> generates k secondary keys and gives them to the user by printing on the screen.
	
The return type of the function is void since it returns nothing to its function call.
*/

void add_locker_entry()
{
	
	// once if we enter this function, we must increment the global_counter to keep track of number of entries in config.txt file
	global_counter++;
	
	
	// asking the user to enter the Locker Id which is a string composed of maximum 5 characters
	printf("Enter LockerId:");
	char *locker_id[5];
	scanf("%s",locker_id);
	
	
	// asking the user to enter the number of users(k)
	printf("Enter Number of Users:");
	int k;
	scanf("%d",&k);
	
	
	// asking the user to enter the Locker key L
	printf("Enter 10 digit Locker Key L:");
	long int L;
	scanf("%ld",&L);
	
	
	
	
	FILE *fp;
	fp = fopen("config.txt","a");		// opening the file config.txt in append mode 
	
	
	int p[k];			// an array to store the set of k prime numbers
	int i,temp_k,temp_L;
	
	
	int modulo_array[k];	// an array to keep track of remainders when L is divided by each of the prime number p[i] 
	int index_of_modulo_array = 0;	// an integer to keep track of size of modulo_array[]
	
	
	temp_k = k;			// a temporary variable to store the value of k
	temp_L = L;			// a temporary variable to store the value of L
	
	
	// we start iterating from the number 2 and find (k - 1) prime numbers. The last (kth) prime number is dealt in the next while loop.
	for(i = 2;temp_k > 1;i++)
	{
		if(isPrime(i))		// if the current value of 'i' is prime, then we go inside this block of code 
		{
			int flag = 0;	// temporary variable to ensure that no two prime numbers (p[i] and p[j]) give same reaminder when L is divided by p[i] and p[j]
			
			if(index_of_modulo_array == 0)	// for the zeroth index of modulo_array[], we directly store (L % i), since this is the first element.
			{
				modulo_array[index_of_modulo_array] = L % i;	// filling the zeroth entry with (L % i)
				index_of_modulo_array++;
				
				p[k-temp_k] = i;		// filling the corresponding entry in prime number array
				temp_k--;				// decrementing the value to maintain the array index of array p[] correctly
				temp_L = temp_L / i;	// to ensure that L > (product of k prime numbers)
				
			}
			
			// once if the modulo_array[] is filled with atleast one entry, then we should iterate among the array to ensure that remainders do not repeat
			else
			{
				for(int j = 0;j < index_of_modulo_array;j++)
				{
					if(L%i == modulo_array[j])
						flag = 1;
				}
				
				if(flag == 0)	// if flag is zero, then the same logic is executed as done for (index_of_modulo_array = 0) case
				{
					modulo_array[index_of_modulo_array] = L % i;
					index_of_modulo_array++;
					
					p[k-temp_k] = i;
					temp_k--;
					temp_L = temp_L / i;
				}
			}
			
			
			
		}
	}
	
	
	// by the end of above loop, we have found (k-1) prime numbers. To find the k th prime number, we use the condition : "kth prime > L / (product of (k-1) primes)"
	while(true)
	{
		
		temp_L++;
		
		int flag = 0;
		if(isPrime(temp_L))		// if the integer is prime, we check again for uniqueness of remainder
		{
			for(int j = 0;j < index_of_modulo_array;j++)
				{
					if(L%(temp_L) == modulo_array[j])
						flag = 1;
				}
			
			if(flag == 0)			// if the remainder is unique, then we have found the kth prime number (p[k - 1] = temp_L + 1)
			{
				p[k - 1] = temp_L;
				modulo_array[index_of_modulo_array] = L % (temp_L);
				index_of_modulo_array++;
				break;
			}
		}
		
			
	}
	
	// By the end of above loop, we have successfully generated k distinct prime numbers satisfying all the constraints.
	
	// Now, as per the question, we print the locker_id,k,all the prime numbers in the desired order.
	fprintf(fp,"%s %d ",locker_id,k);
	
	for(i = 0;i < k;i++)
		fprintf(fp,"%d ",p[i]);
	
	fprintf(fp,"\n");
	
	
	fclose(fp);		// once the required content is entered into the file, we close the file.
	
	// Now the task is to print the unique 4-digit user keys onto the screen to the user.
	// We give the secondary keys u1,...,uk the values stored in modulo_array[] resspectively.
	// since secondary key is exactly 4-digit, we store each key as an array as follows
	
	printf("\nSecondary keys:");
	printf("\n(");
	for(i = 0;i < k;i++)
	{
		
		int j;
		int temp = modulo_array[i];		// temporary variable to store a particular value of modulo_array[]
		int u[4];		// array to store secondary key value
		
		for(j = 3;j >= 0;j--)
		{
			u[j] = temp % 10;		// we take the last digit of temp and store it as the last element of array u[]
			temp = temp / 10;		// reduce temp by dividing with 10 and continue for 4 iterations
		}
		
		
		for(j = 0;j < 3;j++)
			printf("%d",u[j]);
		
		if(i == k-1)
			printf("%d",u[3]);
		else
			printf("%d,",u[3]);
	}
	
	printf(")\n");	
	printf("--------------------\n");
	
	
	// And finally by the end of this loop, we are done with the task of adding a new locker entry.
	// The control shifts back to where this function is called.
	
	return;
	
	
	
}



/*
The following function delete_locker_entry() takes no parameter as input.
	
As the name suggests, the function asks the user to enter the locker_id that needs to be deleted.
The logic is that we do not delete any line from the file config.txt, 
	instead we maintain an array deleted_line_number_array[] to store the line number that is deleted and do not consider those lines in further operations.

We start iterating through the file config.txt in read mode and compare each locker_id with the entered ones.
Once if it matches, we add that particular line number to the array deleted_line_number_array[].
	
The return type of the function is void since it returns nothing to its function call.
*/

void delete_locker_entry()
{
	FILE*fp;
	fp = fopen("config.txt","r+");
	
	
	char input[5];
	int flag = 0; 		// a temporary variable to check if the entered locker id is actually present in config.txt or not
	
	
	printf("Enter the locker id : ");
	scanf("%s",input);
	
	for(int i = 0;i < global_counter;i++)
	{
		int k;		// to store k value for a particular line in config.txt
		char temp[5];		// to store locker_id for a particular line in config.txt
		
		fscanf(fp,"%s %d ",temp,&k);
		
		int p[k];		// to store the k prime numbers (p1,...,pk)
		
		
		
		if(strcmp(temp,input) == 0)		// if the entered locker id matches with a particular locker_id, then we add that line number to array deleted_line_number_array[]
		{
			
			deleted_line_number_array[index_of_deleted_line_number_array] = i;
			index_of_deleted_line_number_array++;
			
			
			printf("\nEntry successfully deleted");
			printf("\n--------------------\n");
			flag = 1;
			
			break;
		}
		
		else
		{
			for(int j = 0;j < k;j++)
			{
				fscanf(fp,"%d ",&p[j]);
			}
		}
			
		fscanf(fp,"\n");
	}
	
	if(flag == 0)
	{
		printf("\nInvalid Entry");
		printf("\n--------------------\n");
	}
	
	fclose(fp);
	return;
}
		
		

/*
The following function euclidian_gcd() takes four parameters as input:
	-> a,b - two integers for which gcd has to be calculated
	-> x,y - two integer pointers that represent constants of Euclidian gcd satisfying the equation :
			a*x + b*y = gcd(a,b)
	
The function returns the integer value gcd(a,b)
Hence the return type is int.
*/

int euclidian_gcd(int a, int b, int *x, int *y)
{
	// Base Case
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}

	int x1, y1; // To store results of recursive call
	int gcd = euclidian_gcd(b%a, a, &x1, &y1);

	// Update x and y using results of recursive call
	*x = y1 - (b/a) * x1;
	*y = x1;

	return gcd;
}



/*
The following function use() takes no parameter as input.
	
The function asks the user to enter locker_id and k distinct user keys. The function trys to reconstruct the locker key L.
After taking the locker_id as input, it checks if it is present in config.txt file or not.
If present, using prime numbers (p1,...,pk) and keys (u1,...,uk), and by using chinese remainder theorem, we construct the key L.
	
The return type of the function is void since it returns nothing to its function call.
*/

void use()
{
	FILE*fp;
	fp = fopen("config.txt","r");
	
	char ch[5];
	printf("\nEnter Locker Id :");
	scanf("%s",ch);
	
	
	for(int i = 0;i < global_counter;i++)
	{
		
		
		int k;
		char temp[5];
		
		fscanf(fp,"%s %d ",temp,&k);
		
		int p[k];
		
		for(int j = 0;j < k;j++)
		{
			fscanf(fp,"%d ",&p[j]);
		}
		
		
		if(strcmp(ch,temp) == 0)	// if the locker_id matches with some string in the file, we go inside the loop
		{
			
			// to ensure that entered locker_id is not deleted, we iterate through the array deleted_line_number_array[]
			for(int count = 0;count < index_of_deleted_line_number_array;count++)			
			{
				if(deleted_line_number_array[count] == i)
				{
					printf("\nThe locker id you entered was already deleted");
					printf("\n--------------------\n");
					fclose(fp);
					return;
				}
			}
			
			int u[k];
			printf("\n");
			
			// asking the user to enter the user keys one by one
			for(int l = 0;l < k;l++)
			{
				printf("Enter userkey %d : ",l+1);
				scanf("%d",&u[l]);
			}
			
			
			// The implementation of Chinese Remainder theorem starts from below :
			
			int m[k];
			int N = 1;
			int counter;
			for(counter = 0;counter < k;counter++)
			{
				N = N * p[counter];				// an integer N to store the product of all prime numbers (p[0]*...*p[k-1])
			}
			for(counter = 0;counter < k;counter++)
			{
				m[counter] = N / p[counter];
			}
			
			int x[k];
			int y[k];
			int e[k];
			int ans = 0;
			
			for(counter = 0;counter < k;counter++)
			{
				int g = euclidian_gcd(p[counter],m[counter],&x[counter],&y[counter]);
				e[counter] = y[counter] * m[counter];
				ans = ans + (u[counter] * e[counter]);
			}
			
			for(counter = p[k-1];counter < N;counter++)
			{
				if((counter - ans) % N == 0)
				{
					printf("\nThe Locker Accesscode is : %d",counter);
					printf("\n--------------------\n");
				}
			}
			
			
		}
		fscanf(fp,"\n");
	}	
	
	return;
}
		
		

/*
The following function configure() takes no parameter as input:

The function gives the user a menu containing three options out of which one has to be selected
It returns nothing to the function call.
Hence the return type is void.
*/

void configure()
{
	int ch2;
	printf("\n1. Add New Locker Entry\n2. Delete a locker entry\n3. Return\n\nMention your preference (1/2/3):");
	scanf("%d",&ch2);
			
	switch(ch2)		// switch case starts
	{
		case 1:		// if 1 is entered, we go to the add_locker_entry() function
		{
			add_locker_entry();
			break;
		}
		
		case 2:		// if 2 is entered, we go to the delete_locker_entry() function
		{
			delete_locker_entry();
			break;
		}
		
		case 3:		// if 3 is entered, we return back to where function is called 
			return;
		
		default:	// as a base case, we print an apt message if an invalid choice is entered
			printf("Please enter a valid choice");
			
	}
}


// main function starts
int main()
{
	
	open_empty_file();		// opening the config.txt file and making the contents of the file empty.
	
	int ch1;
	while(true)				// an infinite loop that displays the menu to the user 
	{
		printf("\n1.CONFIGURE\n2.USE\n3.EXIT\n\nMention your preference (1/2/3):");
		scanf("%d",&ch1);
		
		// switch case starts 
		switch(ch1)
		{
			
			case 1:			// if 1 is entered, the control enters configure() function
			{
				configure();
				break;
			}
			
			case 2:			// if 2 is entered, the control enters use() function
			{
				use();
				break;
			}
			
			case 3:			// if 3 is entered, we terminate the program 
			{
				printf("Program termination");
				exit(0);
				break;
			}
			
			default:		// as a base case, we print an apt message if an invalid choice is entered
				printf("Please enter a valid choice");			
					
			
		}
		
	}
	
	return 0;
	
}
