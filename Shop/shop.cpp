#include<bits/stdc++.h>

using namespace std;
class Product
{	
	private:
		int id1;
		string name;
	public:
		Product(int id1, string name):id1(id1), name(name){}
		int getId()
		{
			return id1;
		}
		
		bool operator<(const Product& other) const
		{
			return id1 < other.id1;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const Product& item)
	    {
	        os << "( " << item.id1 << " ) " << item.name;
	
	        return os;
	    }
					

};

class Shop 
{
	private:
		int id1;
		string name;
		string address;
	public:
		map<Product, pair<int, int> > products; 
		Shop(int id1, string name, string address):id1(id1), name(name), address(address){}	
		void add(int id, string name, int count, int price)
		{
			products.insert(make_pair(Product(id,name), make_pair(count, price)));
		}
		const std::map<Product, std::pair<int, int>>& getProducts() const
		{
			return products;
		}
		
		friend ostream& operator<<(ostream& os, Shop &sh)
		{
			os << "( " << sh.id1 << " ) " << sh.name << " : " << sh.address << std::endl << "=========================" << std::endl;
			for (auto &item : sh.products)
			    os << item.first << ": count = " << item.second.first << "  price = " << item.second.second << std::endl;
			return os;
		}
		string getName()
		{
			return name;
		}
		int getshopID()
		{
			return id1;
		}
};

		

int main()
{
	Shop shop1 = Shop(1, "UG", "Hunnu");
	Shop shop2 = Shop(2, "MA", "Officer");
	Shop shop3 = Shop(3, "AJ", "Khorolol");
	
	Product potato = Product(1, "Potato");
	Product carrot = Product(2, "Carrot");
	Product pie = Product(3, "Pie");
	Product celery = Product(4, "Celery");
	Product cake = Product(5, "cheesecake");
	Product book = Product(6, "Tolstoy");
	Product cabbage = Product(7, "Mongolian");
	Product flour = Product(8, "Atar");
	Product onions = Product(9, "Mongolian");
	Product beets = Product(10, "Mongolian");
	Product sirok = Product(11, "Russian");
	Product chocolate = Product(12, "Belgium");

	shop1.add(1, "Potato", 5, 79);	
	shop1.add(2, "Carrot", 4, 23);	
	shop1.add(3, "Pie", 2, 100);	
	shop1.add(4, "Potato", 5, 55);	
	shop1.add(5, "Carrot", 4, 44);	
	shop1.add(6, "Pie", 2, 22);		
	shop1.add(7, "Potato", 5, 23);	
	shop1.add(8, "Carrot", 4, 24);	

	shop2.add(11, "Pie", 1, 99);		
	shop2.add(10, "Potato", 11, 88);	
	shop2.add(9, "Carrot", 40, 200);	
	shop2.add(8, "Pie", 88, 100);		
	shop2.add(7, "Potato", 66, 15);	
	shop2.add(6, "Carrot", 22, 11);	
	shop2.add(5, "Pie", 33, 55);		
	shop2.add(4, "Potato", 99, 21);	
	shop2.add(3, "Carrot", 77, 17);	
	shop2.add(2, "Pie", 55, 100);	
	
	shop3.add(1, "Pie", 7, 300);		
	shop3.add(2, "Potato", 5, 2000);	
	shop3.add(3, "Carrot", 3, 1000);	
	shop3.add(4, "Pie", 1, 4);		
	shop3.add(5, "Potato", 11, 10);	
	shop3.add(6, "Carrot", 13, 10);	
	shop3.add(7, "Pie", 77, 10);		
	shop3.add(8, "Potato", 44, 156);	
	shop3.add(9, "Carrot", 4, 892);	
	shop3.add(10, "Pie", 2, 293);	
	
	cout << shop1.getshopID() << ": " << shop1.getName() << '\n';
	for (auto &item : shop1.products)
			    cout << item.first << ": count = " << item.second.first << "  price = " << item.second.second << std::endl;
	cout << shop2.getshopID() << ": " << shop2.getName() << '\n';
	for (auto &item : shop2.products)
			    cout << item.first << ": count = " << item.second.first << "  price = " << item.second.second << std::endl;
	cout << shop3.getshopID() << ": " << shop3.getName() << '\n';
	for (auto &item : shop3.products)
			    cout << item.first << ": count = " << item.second.first << "  price = " << item.second.second << std::endl;
}


 

