
#include "list.h"

class Ordered_list:public List<int>{
public:
   Ordered_list();
   Error_code insert(const int &data);
   Error_code insert(int position, const int &data);
   Error_code replace(int position, const int &data);
};