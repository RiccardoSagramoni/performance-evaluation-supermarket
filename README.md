# PECSN-Supermarket
Project for the **Performance Evaluation of Computer Systems and Networks** (MSc Computer Engineering at University of Pisa, A.Y. 2021-22), made by Riccardo Sagramoni, Niko Salamini and Fabrizio Lanzillo.

The aim of the project was to design and develop with **Omnet++ 5.7** a simulator of a supermarket, then evaluate its performance in several meaningful scenarios.

The project was developed on *Ubuntu 20.04*.

## Specifications
A supermarket has n tills. Two policies can be enforced for checkout:

* **Undistinguished tills**: any customer can check out at any till.
* **Quick-checkout tills**: a percentage p of tills is reserved for customers whose shopping cart
holds less than k items (k being the quick-checkout threshold).

In both cases, a customer queues up at the till with the smallest queue among those where (s)he is
allowed to queue. 

Consider the following workload: customer inter-arrival times are IID RVs (to be
described later), their service demands (i.e., checkout times) are IID RV (to be described later). The
percentage of quick-checkout tills can be varied (but stays constant in a single simulation), and so
does k.

Compare the ***queueing and response time*** of the two options under a varying workload. More in detail,
at least the following scenarios must be evaluated:
- <ins>Exponential</ins> distribution of interarrival times and service demands.
- <ins>Lognormal</ins> distribution of service demands.
