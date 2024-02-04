# Finesse
The most popular approach to determine the similarity of data for delta compression is the "N-transform superfunctional" (N-transform SF). However, computing the N-transform SF requires large computational resources: for each data fragment, a linear transformation must be applied N times to its Rabin footprint. To simplify this process, we can exploit the feature locality that exists among very similar fragments.
Therefore, Finesse method was proposed which is based on feature locality and fast similarity detection. It divides each fragment into several sub-fragments of fixed size, computes the features for each sub-fragment separately, and then combines them into superfunctions. Experiments have shown that compared to the state-of-the-art N-transform based SF approach, the Finesse method speeds up similarity computation by a factor of 3.2-3.5 and increases deduplication and delta compression system throughput by 41-85%, while achieving comparable compression ratios.
### Superfunction approach
Similarity Determination - is the first step required for delta compression, which allows computing the similarity of data fragments and finding candidates for compression. As mentioned above, currently the most popular method for similarity detection at the fragment level is the "N-transform SF" approach. It was first proposed by Broder and is based on "Broder's theorem" which evaluates the similarity between two sets as shown below:
Theorem 1: Consider two sets A and B, with H(A) and H(B) being the corresponding hash sets of elements of A and B respectively, where H is chosen uniformly and randomly from a minimally independent family of permutations. An element of the set is mapped to an integer. Let min(S) denote the smallest element of the set of integers S. Then:
Pr⁡〖[min〗⁡(H(A)) =min⁡(H(B))]=  (|A∩B|)/(|A∪B|)
Broder's theorem states that the probability that two sets A and B have the same minimum hash element is equal to their Jaccard similarity coefficient. Based on this theorem, Broder proposed a similarity detection approach called superfunctions, which extracts a fixed number of features from a fragment. Specifically, this SF-based approach computes the similarity of data by extracting features from Rabin fingerprints (convolutional hash algorithm) and then clustering these features in SF for similarity detection to reduce the amount of data. For example, a chunk feature (length = L) is uniquely generated using a randomly given pair of values mi and ai (i.e., linear transformation) and L Rabin fingerprints (as used in Content-Defined Chunking) with a sliding window size of 48 bytes as follows:
〖Feature〗_i= 〖Max〗_(j=1)^L {(m_i*〖Rabin〗_j+a_i)mod2^32}
where 〖Rabin〗_j is the Rabin footprint of the sliding window method located at position j)
Thus, fragments that have one or more common features (maximum values) are likely to be very similar, and small changes in the data are unlikely to affect the maximum values. Algorithm 1 provides a detailed pseudo-code implementation of feature extraction using the N-transform SF. The superfunction of a given chunk, SFx, can then be computed from several such features as follows:
〖SF〗_x=Rabin(〖Feature〗_(x*k),…,〖Feature〗_(x*k+k-1))
For example, to generate three SFs with k=4 features in each, we must first generate N=12 features, namely, features 0...3 for SF0, features 4...7 for SF1, etc. For identical chunks differing by only a small fraction of a byte, most of the features will be identical, hence SF. More specifically, this N-transform SF approach maximises the detection of very similar chunks for two reasons:
1.	The matching of a single SF means that almost all features grouped in that SF are identical, hence grouping features into SFs reduces the number of false positives in similarity detection. 
2.	To increase the detection probability of very similar fragments, multiple SFs are computed. 
Meanwhile, this N-transform SF approach needs to linearly transform the Rabin fingerprints of the data fragments N times, which takes a lot of time and slows down the whole delta compression process after deduplication.
It should be noted that there are also a number of other approaches for coarse-grained similarity detection for matching similar files or large data blocks (e.g., 16MB in size) that extract features from non-overlapping rows (or chunks) and therefore may suffer from a large number of false positives. This paper focuses on improving the most popular SF approach with N-transform for chunk-level similarity detection in a delta-compression scenario after deduplication.
![image](https://github.com/XAH30/LSH-vs-Finesse/assets/73390555/c2ef052f-f028-4f73-bc6d-7d3de3f0ad33)
An example of the existence of fine-grained locality among two identical chunks

Here each chunk is divided into N subchunks of fixed size. The corresponding subchunks in block B are very similar (one-to-one) to the subchunks in block A, and therefore their characteristics are very much the same.
