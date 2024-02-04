set<pair<int, int>> Finesse(const vector<Chunk>& chunks, size_t subchunkSize, double similarityThreshold) {
    unordered_map<string, Feature> featuresMap;
    vector<string> deltaCodes;
    set<pair<int, int>> similarChunksSet;  // Множество для хранения пар похожих чанков

    for (size_t i = 0; i < chunks.size(); i++) {
        const Chunk& chunk = chunks[i];
        const vector<Subchunk>& chunkSubchunks = splitIntoSubchunks(chunk, subchunkSize);

        for (size_t j = 0; j < chunkSubchunks.size(); j++) {
            const Subchunk& subchunk = chunkSubchunks[j];
            string featureHash = RabinFingerPrint(subchunk, i * chunkSubchunks.size() + j);

            if (featuresMap.count(featureHash) > 0) {
                continue;
            }

            Feature feature(featureHash);
            featuresMap[featureHash] = feature;

            size_t numSubchunksToCompare = static_cast<size_t>(static_cast<double>(chunkSubchunks.size()) * similarityThreshold);

            for (size_t k = i + 1; k < chunks.size(); k++) {
                const Chunk& otherChunk = chunks[k];
                const vector<Subchunk>& otherChunkSubchunks = splitIntoSubchunks(otherChunk, subchunkSize);

                size_t numSimilarSubchunks = 0;

                for (size_t l = 0; l < otherChunkSubchunks.size(); l++) {
                    const Subchunk& otherSubchunk = otherChunkSubchunks[l];

                    if (isSimilar(subchunk.getData(), otherSubchunk.getData(), similarityThreshold)) {
                        string deltaCode = deltaCompression(chunk, otherSubchunk);
                        deltaCodes.push_back(deltaCode);

                        numSimilarSubchunks++;
                    }
                }

                // Если количество похожих подчанков достигло порога, выходим из цикла
                if (numSimilarSubchunks >= numSubchunksToCompare) {
                    // Сохраняем пару похожих чанков в множество
                    similarChunksSet.insert(make_pair(i, k));

                    break;
                }
            }
        }
    }

    return similarChunksSet;
}