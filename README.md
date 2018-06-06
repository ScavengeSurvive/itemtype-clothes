# itemtype-clothes

[![sampctl](https://shields.southcla.ws/badge/sampctl-itemtype--clothes-2f2f2f.svg?style=for-the-badge)](https://github.com/ScavengeSurvive/itemtype-clothes)

Clothes item type - allows changing skin via an item.

## Installation

Simply install to your project:

```bash
sampctl package install ScavengeSurvive/itemtype-clothes
```

Include in your code and begin using the library:

```pawn
#include <itemtype-clothes>
```

## Usage

Set which item is the clothes item with `DefineItemTypeClothes`.

Define clothes types with `DefineClothesType`.

### In Game

Pick up a clothes item and hold the interact key to change.

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` and try out the clothes items in front of you.
