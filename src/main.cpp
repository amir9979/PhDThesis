#include "spectra.h"
#include "count_spectra.h"
#include "similarity.h"
#include "spectra_filter.h"
#include "spectra_iterator.h"

#include "trie.h"

#include "mhs.cpp"

#include <iostream>


using namespace std;



void test_mhs() {
  t_count_spectra count_spectra(3,3);
  count_spectra.hit(1,1); 
  count_spectra.hit(2,2); 
  count_spectra.hit(3,3); 
  count_spectra.hit(1,3); 
  count_spectra.hit(3,1); 
  count_spectra.hit(3,2); 
  count_spectra.error(1);
  count_spectra.error(2);
  t_mhs<t_count> mhs((t_ochiai<t_count>()));
  t_trie D;
  mhs.calculate(count_spectra, D);
}

void test_spectra() {
  t_spectra_filter filter;
  //t_spectra_iterator it(4,4);
  t_spectra_iterator it(3,3, &filter);
//  filter.filter_component(1);
  //filter.filter_component(2);
  //filter.filter_component(4);
  //filter.filter_transaction(4);
  //filter.filter_transaction(2);
  //filter.filter_transaction(1);
  //filter.filter_transaction(3);

  while(it.next(true)){
    cout << it.get_component() << ", " << it.get_transaction() << endl; 
  }
  cout << "--------\n";
  while(it.next(false)){
    cout << it.get_component() << ", " << it.get_transaction() << endl; 
  }

  t_count_spectra count_spectra(3,3);
  count_spectra.hit(1,1); 
  count_spectra.hit(2,2); 
  count_spectra.hit(3,3); 
  count_spectra.hit(1,3); 
  count_spectra.hit(3,1); 
  count_spectra.hit(3,2); 
  count_spectra.error(1);
  count_spectra.error(2);
  cout << count_spectra;
  count_spectra.print(cout, NULL);
  count_spectra.print(cout, &filter);
  t_ochiai<t_count> ochiai;
  unique_ptr<t_rank_element[]> order_buffer = count_spectra.get_ordering_buffer();

  ochiai.order(count_spectra, NULL, order_buffer.get());
  for(int i = 0; i < count_spectra.get_component_count(); i++){
    cout << order_buffer[i].get_component() << "," << order_buffer[i].get_value() << " " ;
  }
  cout << endl;
  ochiai.order(count_spectra, &filter, order_buffer.get());
}

void test_trie() {
  t_trie trie;
  int option;
  t_candidate candidate;


  while (scanf("%d", &option) > 0){
    candidate.clear();
    puts("---------");
    switch(option) {
      case 1:
        while (scanf("%d", &option) > 0) {
          if(option < 1)
            break;
          candidate.insert(option);
        }
        trie.add(candidate);
        trie.print(cout);
        break;
      case 2:
        while (scanf("%d", &option) > 0) {
          if(option < 1)
            break;
          candidate.insert(option);
        }
        if(trie.is_composite(candidate))
          puts("True");
        else
          puts("False");
        break;
      default:
        return;
    }
  
  }

}
int main(){
  test_trie();

}


