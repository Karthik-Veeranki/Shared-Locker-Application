# Shared-Locker-Application

This is a real life application program in which there is a Bank Locker System that is to be shared among 'k' users. All the users have to be present to access the locker.

Basically, there are two modules - CONFIGURE and USE.

CONFIGURE module:

In this module, all the 'k' users will give a primary key 'L', a unique locker ID and the value k as input. Now, we generate k distinct prime numbers p1,p2,...,pk satisfying the condition that p1.p2....pk > L
Based on these k prime numbers, each of these k users will be provided with a unique four digit secondary key. Uniqueness is ensured from the fact that those secondary keys are remainders obtained respectively by dividing L by those prime numbers.
Once everything is done, we allot all these secondary keys to the users and store only prime numbers in a txt file.
By this we maintain privacy and security by not storing the primary key and secondary keys.

Also the bank authorities has the option to delete a locker entry if they wish by calling delete function. Basically, we store that locker ID which is deleted and not permanantly removing it. In this way, we give show the user that entry is deleted at the same time, store the deleted entries (similar to recycle bin).

USE module:

If the k users provide their respective k secondary keys, using the already stored k prime numbers, we will be able to construct the primary key L using the concept of Chinese Remainder Theorem.
By this way, all the k users have to be present to open the locker.
