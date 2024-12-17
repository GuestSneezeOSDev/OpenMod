/* -----------------------------------------------------------------------------
 * See the LICENSE file for information on copyright, usage and redistribution
 * of SWIG, and the README file for authors - http://www.swig.org/release.html.
 *
 * std_list.i
 *
 * SWIG typemaps for std::list types
 * 
 * To use, add:
 * 
 * %include "std_list.i"
 *
 * to your interface file. You will also need to include a template directive
 * for each instance of the list container you want to use in your application.
 * e.g.
 * 
 * %template (intlist) std::list<int>;
 * %template (floatlist) std::list<float>;
 * ----------------------------------------------------------------------------- */

%module std_list
%warnfilter(468) std::list;

%{
#include <list>
#include <stdexcept>
%}


namespace std{
    template<class T> class list
    {
    public:
	     
	typedef T &reference;
	typedef const T& const_reference;
	typedef T &iterator;
	typedef const T& const_iterator; 
	    
	list();
	list(unsigned int size, const T& value = T());
	list(const list<T> &);

	~list();
	void assign(unsigned int n, const T& value);
	void swap(list<T> &x);

	const_reference front();
	const_reference back();
	const_iterator begin();
	const_iterator end();
	     
	void resize(unsigned int n, T c = T());
	bool empty() const;

	void push_front(const T& INPUT);
	void push_back(const T& INPUT);


	void pop_front();
	void pop_back();
	void clear();
	unsigned int size() const;
	unsigned int max_size() const;
	void resize(unsigned int n, const T& INPUT);
		
	void remove(const T& INPUT);
	void unique();
	void reverse();
	void sort();

	%extend 
	    {
	        %typemap(lout) T &__getitem__ "(cl::setq ACL_ffresult (ff:fslot-value-typed '$*out_fftype :c $body))";
		%typemap(lout) T *__getitem__ "(cl::setq ACL_ffresult (make-instance '$lclass :foreign-address $body))";

		const_reference __getitem__(int i) throw (std::out_of_range) 
		    {
			std::list<T>::iterator first = self->begin(); 
			int size = int(self->size());
			if (i<0) i += size;
			if (i>=0 && i<size)
			{
			    for (int k=0;k<i;k++)
			    {
				first++;
			    }
			    return *first;
			}
			else throw std::out_of_range("list index out of range");
		    }
		void __setitem__(int i, const T& INPUT) throw (std::out_of_range)
		    {
			std::list<T>::iterator first = self->begin(); 
			int size = int(self->size());
			if (i<0) i += size;
			if (i>=0 && i<size)
			{
			    for (int k=0;k<i;k++)
			    {
				first++;
			    }
			    *first = INPUT;
			}
			else throw std::out_of_range("list index out of range");
		    }
		void __delitem__(int i) throw (std::out_of_range)
		    {
			std::list<T>::iterator first = self->begin(); 
			int size = int(self->size());
			if (i<0) i += size;
			if (i>=0 && i<size)
			{
			    for (int k=0;k<i;k++)
			    {
				first++;
			    }
			    self->erase(first);
			}
			else throw std::out_of_range("list index out of range");
		    }	     
		std::list<T> __getslice__(int i,int j) 
		    {
			std::list<T>::iterator first = self->begin();
			std::list<T>::iterator end = self->end();

			int size = int(self->size());
			if (i<0) i += size;
			if (j<0) j += size;
			if (i<0) i = 0;
			if (j>size) j = size;
			if (i>=j) i=j;
			if (i>=0 && i<size && j>=0)
			{
			    for (int k=0;k<i;k++)
			    {
				first++;
			    }
			    for (int m=0;m<j;m++)
			    {
				end++;
			    }
			    std::list<T> tmp(j-i);
			    if (j>i) std::copy(first,end,tmp.begin());
			    return tmp;
			}
			else throw std::out_of_range("list index out of range");
		    }
		void __delslice__(int i,int j) 
		    {
			std::list<T>::iterator first = self->begin();
			std::list<T>::iterator end = self->end();

			int size = int(self->size());
			if (i<0) i += size;
			if (j<0) j += size;
			if (i<0) i = 0;
			if (j>size) j = size;
	
			for (int k=0;k<i;k++)
			{
			    first++;
			}
			for (int m=0;m<=j;m++)
			{
			    end++;
			}		   
			self->erase(first,end);		
		    }
		void __setslice__(int i,int j, const std::list<T>& v) 
		    {
			std::list<T>::iterator first = self->begin();
			std::list<T>::iterator end = self->end();

			int size = int(self->size());
			if (i<0) i += size;
			if (j<0) j += size;
			if (i<0) i = 0;
			if (j>size) j = size;
		
			for (int k=0;k<i;k++)
			{
			    first++;
			}
			for (int m=0;m<=j;m++)
			{
			    end++;
			}
			if (int(v.size()) == j-i) 
			{
			    std::copy(v.begin(),v.end(),first);
			}
			else {
			    self->erase(first,end);
			    if (i+1 <= int(self->size())) 
			    {
				first = self->begin();
				for (int k=0;k<i;k++)
				{
				    first++;
				}
				self->insert(first,v.begin(),v.end());
			    }
			    else self->insert(self->end(),v.begin(),v.end());
			}
			   	
		    }
		unsigned int __len__() 
		    {
			return self->size();
		    }	
		bool __nonzero__()
		    {
			return !(self->empty());
		    }
		void append(const T& INPUT)
		    {
			self->push_back(INPUT);
		    }
		void pop()
		    {
			self->pop_back();
		    }
	      
	    };   
    };
}






