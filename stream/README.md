
# Optimizing JSON stream for web and mobile endpoints.
 * sets - defines datasets included in meta/frame/dict
 * dict - data dictionary hosting dataset index and field order used to assemble query results 
 * meta - descriptor defining fuzzy lookup for use with omni suggest/search functionality 
 * frame - omni search initial load/query results hosting datasets


Metrics:
```console
stream-legacy: 199,774 bytes
stream-opt 35,250 bytes 

// 200 records achieved 5.5x reduction in size
```

Model:
 * sets[[set-id, name][filter, total]]
 * dict[dataset-id, meta-name, [field-name, ...]] 
 * meta[dataset-id, [meta-name, [field-id, ...], ['field-value', '...']]]
 * frame[dataset-id, [field-value, ...]]


Notes: 
 * VIN and stock are distinct listings of the current inventory. Stock meta is only populated if the dealership uses something other than the last 6/8 characters of the VIN.
 * Stock meta would be empty if the dealership uses last 6/8 or leaves the stock field blank.
 * Stock meta is only populated with entries where the stock differs from last 6/8 characters of the VIN.

## Levenshtein Algorithm 
Also known as fuzzy matching, is populated with meta and provides omni with suggestions.
Precedence is defined by the order of items in the sets.

Use Case:
* User types 'Porsch' in omni-search field
* Algorithm returns make-id of 1 conf of 98% and auth-id of 'porscia-evans' conf of 90%
* omni-search suggests Porsche followed by vinpoint user 'porscia-evans'
* User dispatches request by selecting/auto-completing/etc Porsche suggestion
* Node dispatches query to api /vinpoint-api/v1/or/version/agnostic/utopia/?
* SQL dispatches query SELECT OrgId, DealershipId, MakeId, ModelId, CreatedEpoch, ... FROM ONE_TABLE_NO_JOINS
* API returns data in framed format including meta/frame/dict.
* javascript assembles framed data using dict to map fields to appropriate field elements in browser.

### Example JSON Format
```json
{
    "data": {
        "sets": [[0, "inv"], [1, "auth"]],
        "dict": [
            [0, "inv", ["org-id", "dealer-id", "mileage", "created-epoch", "last-label-epoch", "inventory-id", "vin", "year", "make-id", "model-id", "stock", "color-id", "class-id", "location-id", "lat", "lng", "sig", "3pa", "scanned-epoch"]]
            [1, "auth", ["user-id", "email", "first", "last", "last-login-epoch"]]
        ],             
        "meta": [
            [0, ["org", [1, 2], [ "Cobb Porsche", "Cobb McLaren"]]],
            [0, ["dealership", [100, 200], ["Cobb Porsche", "Cobb McLaren"]]],
            [0, ["location", [1, 2], ["Lot 1", "Parking Garage"]]],
            [0, ["make", [1, 2], ["Porsche", "McLaren"]]],
            [0, ["model", [1, 2], ["911", "720 S"]]],
            [0, ["color", [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], ["White", "Silver", "Grey", "Black", "Yellow", "Orange", "Tan", "Brown", "Purple", "Red", "Blue", "Green"]]],
            [0, ["class", [1, 2, 3, 4, 5], ["New", "Used", "Loaner", "Uber", "Lyft"]]],
            [1, ["auth", [1, 2, 3], ["@porscia.evans", "@jane.smith", "@peter.parker"]]]            
        ],    
        "frame": [         
            [0, [1, 100, 558853, 0, 325452225, 325452232, 317919, "WP1AA2A50KLB01949", 2019, 1, 1, "KLB01949", 3, 2, 1, 32768011, -106374481, 5.7, 0, 325452232]],
            [0, [1, 100, 558853, 0, 325452225, 325452232, 317919, "SBM14DCA8JW001553", 2018, 2, 2, "JW001553", 3, 2, 2, 28768011, -105352845, 5.2, 0, 325452185]],
            [1, [1, "@porscia-evans", "porscia@vinpoint.io", "Porscia", "Evans", 325452187]]
        ]
    }
}
```

