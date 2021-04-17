You are given an amount of money to purchase a pair of jeans, a pair of socks, a shirt, and a pair of shoes. You are also given the price
options for each of the merchandise as the input, in the following order: jeans, socks, shirt, and shoes
For example:
2 3 --> there are 2 jean prices, priced at 2,3
4
2 3
2 1
20 --> This is your budget
Your job is to print your possible purchase combination. Also print your combination. In this case we have 4 combinations

I cannot get around to lower the worst case scenario, and I cannot see any repeating patterns or the optimal sub-structure required by dynamic programming.
If there are N types of items, and each of the items has M, the worst case is O(M^N). Still polynomial, but quite horrible. 
