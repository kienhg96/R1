##### Usage:
`coccoc "many words" [path to dictionary]`
Example: `coccoc "hello, world" ./sample_data`

##### Save index data and query:
`coccoc "many words" [path to dictionary] -s <path to save index data>`
Example: `coccoc "hello, world" ./sample_data -s ./index.dat`

##### Index only and save index data:
`coccoc [path to dictionary] -i <path to save index data>`
Example: `coccoc ./sample_data -i ./index.dat`

##### Load index data and query:
`coccoc "many words" -r <path to saved index data>`
Example: `coccoc "hello, world" -r ./index.dat`
