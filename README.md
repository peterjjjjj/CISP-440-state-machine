zhu yao shi 
for (int j = s + 1; j > 0; --j) {
                if (strncmp(sequence, &got[s + 1 - j], j) == 0) {
                    nextstate = j;
                    break;
                }
            }

dont understand
