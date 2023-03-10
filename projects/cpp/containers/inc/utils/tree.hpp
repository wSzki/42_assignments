/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsz </var/spool/mail/wsz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:42:15 by wsz               #+#    #+#             */
/*   Updated: 2022/10/24 12:42:16 by wsz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#include <iostream>
#include <cstddef>
#include <memory>
#include <functional>

/* ========================================================================== */
/* ---------------------------------- NODE ---------------------------------- */
/* ========================================================================== */
template <typename Key, typename Data>
struct node {

	Key    first;
	Data   second;
	node * left;
	node * right;
	node * parent;
	node * end;
	//node * root;

	node (
			Key    key_    = 0,
			Data   data_   = 0,
			node * parent_ = NULL,
			node * left_   = NULL,
			node * right_  = NULL,
			node * end_    = NULL
			//node * root_   = NULL
		 )
	{
		first    = key_    ;
		second   = data_   ;
		parent   = parent_ ;
		left     = left_   ;
		right    = right_  ;
		end      = end_    ;
		//root = root_;
	};

	Key operator * (void) { return first; }

};

/* ========================================================================== */
/* ---------------------------------- TREE ---------------------------------- */
/* ========================================================================== */
template <typename Key, typename Data, typename Compare, typename Alloc_type>
class tree
{
	/* .............................................. */
	/* .................. TYPEDEFS .................. */
	/* .............................................. */
	public:
		typedef node<Key,Data>                  node_t;
		typedef node_t *                        nodePtr;
		//typedef typename std::allocator<node_t> Alloc;
		typedef typename Alloc_type::template rebind<node <Key, Data> >::other Alloc;
		typedef Compare							key_compare;

		/* .............................................. */
		/* ............. VARIABLE  MEMBERS .............. */
		/* .............................................. */
	protected:
		node_t * node_root;
		node_t * node_current;
		node_t * node_last_inserted;
		node_t * end;

		key_compare comp;
		Alloc       alloc;
		size_t      number_leaves;
		//std::less<Key> compare; // equivalent to '<' ,(compare(a, b)) // TODO this is supposed to be associated to typename Compare

	public:

		/* .............................................. */
		/* ................. ALLOCATOR .................. */
		/* .............................................. */
		nodePtr allocate_node (
				Key     key    = Key(),
				Data    data   = Data(),
				nodePtr parent = NULL,
				nodePtr left   = NULL,
				nodePtr right  = NULL
				//nodePtr root = NULL
				)
		{
			if (left   == NULL) left   = end;
			if (right  == NULL) right  = end;
			nodePtr new_node = alloc.allocate(1);
			//if (size() != 0)
			//root = get_node_root();
			alloc.construct(new_node, node_t(key, data, parent, left, right, end));
			return new_node;
		}

		/* .............................................. */
		/* ................. CONSTUCTOR ................. */
		/* .............................................. */
		tree (void) {
			end           = NULL;
			end           = allocate_node(Key(), Data(), NULL, NULL, NULL); // Generating a dummy node pointer as a delimiter
			end->left     = end;
			end->right    = end;
			end->parent   = end;
			node_root     = NULL;
			// std::cout << "END TREE: " << end << std::endl;
			number_leaves = 0;
		};

		/* .............................................. */
		/* ................. DESTRUCTOR ................. */
		/* .............................................. */
		~tree() { chop_tree(node_root); alloc.destroy(end); alloc.deallocate(end, 1); end = NULL; node_root = NULL ; number_leaves = 0;}

		void clear() { chop_tree(node_root); alloc.destroy(end); alloc.deallocate(end, 1); end = NULL; node_root = NULL; number_leaves = 0; }


		void chop_tree(nodePtr n)
		{
			// NOTE check for NULL if there is only node end in tree
			if (n == end || n == NULL) return;
			chop_tree(n->left);
			chop_tree(n->right);
			alloc.destroy(n);
			alloc.deallocate(n, 1);
		}

		/* .............................................. */
		/* ................... INSERT ................... */
		/* .............................................. */
		// NOTE Does nothing if key already exists
		// NOTE & is needed to modify the node pointer's address within the function
		// NOTE node == NULL if tree has just been initialized

		nodePtr insert (const Key key, Data data) {
			insert(key, data, node_root, end);
			return node_last_inserted;
		}

		void insert (const Key key, Data data, nodePtr & node, nodePtr node_parent)
		{
			if   (node == end || node == NULL)
			{
				node = allocate_node(key, data, node_parent);
				node_last_inserted = node;
				number_leaves++;
				return ;
			}
			if   (key  == node->first) return ;
			if   (comp(key, node->first)) insert(key, data, node->left, node);
			else                       insert(key, data, node->right, node);
		}

		/* .............................................. */
		/* .................... FIND .................... */
		/* .............................................. */
		// NOTE returns nodePtr * end if nothing found
		nodePtr	find_key (const Key k, nodePtr n = NULL) const {
			//if (n == end || n == NULL) return (end) ;
			if (n == NULL)   n = node_root;
			if (n == end || n == NULL)    return (end) ;
			if (k == n->first) return (n);
			if (comp(k, n->first)) return (find_key(k, n->left));
			else               return (find_key(k, n->right));
		}

		nodePtr	find_data (const Data d, nodePtr n = NULL) const {
			//if (n == end || n == NULL) return (end) ;
			if (n == NULL)    n = node_root;
			if (n == end)     return (end) ;
			if (d == n->data) return (n);
			if (comp(d <  n->data)) return (find_data(d, n->left));
			else              return (find_data(d, n->right));
		}

		/* .............................................. */
		/* ................... ERASE .................... */
		/* .............................................. */
		void erase(const Key key) {
			nodePtr node = find_key(key, node_root);
			if (node == NULL || node == end)
				return;
			prune(node); number_leaves--;
		}

		bool single_leaf   (void)         { return (number_leaves == 1) ;                                       }
		bool no_branches   (nodePtr node) { return (node->left == end && node->right == end);                   }
		bool two_branches  (nodePtr node) { return (node->left != end && node->right != end);                   }
		bool single_branch (nodePtr node) { return (no_branches(node) == false && two_branches(node) == false); }
		bool is_root       (nodePtr node) { return (node == node_root);                                         }
		bool is_not_root   (nodePtr node) { return (node != node_root);                                         }

		//bool is_next_valid (nodePtr node_next) { return (node_next->right != end && node_next->right != node_next);}

		void two_branches_delete(nodePtr node) {
			nodePtr node_next = next(node);
			if (is_root(node)) {

				// 1
				if (node_next->right != end && node->right != node_next) {
					node_next->parent->left  = node_next->right;
					node_next->right->parent = node_next->parent;
				}

				// 2
				else if (node->right != node_next)
					node_next->parent->left = end;

				//3
				if (node->right != end && node->right != node_next)
					node->right->parent = node_next;

				// 4
				if (node->left != end)
					node->left->parent = node_next;

				// 5
				node_next->parent = node->parent;
				node_next->left = node->left;
				if (node->right != node_next)
					node_next->right = node->right;
				node_root = node_next;
			}
			else {
				if (node_next->right != end && node->right != node_next) {
					node_next->parent->left = node_next->right;
					node_next->right->parent = node_next->parent;
				}
				else if (node->right != node_next)
					node_next->parent->left = end;

				if (node->left != end) {
					node->left->parent = node_next;
					node_next->left = node->left;
				}

				node_next->parent = node->parent;
				if (node->parent->right == node) {
					node->parent->right = node_next;
				}
				else if (node->parent->left == node) {
					node->parent->left = node_next;
				}
				if (node->right != node_next) {
					node->right->parent = node_next;
					node_next->right = node->right;
				}
			}
		}

		void prune(nodePtr & node)
		{
			nodePtr parent = node->parent;
			if      (single_leaf()) node_root = end;
			else if (no_branches(node)) parent->left == node ? parent->left = end : parent->right = end;
			else if (two_branches(node)) two_branches_delete(node);
			else if (single_branch(node)) {
				nodePtr child = (node->left != end ? node->left : node->right);
				if      (node == node_root)     { node_root     = child; child->parent = end;    }
				else if (node == parent->left)  { parent->left  = child; child->parent = parent; }
				else if (node == parent->right) { parent->right = child; child->parent = parent; }
			}
			alloc.destroy(node);
			alloc.deallocate(node, 1);
		}

		// Used for prune() - see above
		nodePtr smallest_node_from(nodePtr node) { while (node->left  != node->end && node->left != NULL) node = node->left ; return node; }
		nodePtr next(nodePtr current)
		{
			nodePtr end = current->end;
			if (current->right != end)
				return smallest_node_from(current->right);

			nodePtr parent = current->parent;
			while (parent != end && current == parent->right)
			{
				current = parent;
				parent = current->parent;
			}

			if (parent == NULL)
				return end;
			return parent;
		}



		/* .............................................. */
		/* ................... UTILS .................... */
		/* .............................................. */
		size_t size     () const {return (number_leaves);}
		bool   empty    () const {return (size() == 0);}
		size_t max_size () const {return (alloc.max_size());}

		nodePtr		getMin (nodePtr n = NULL) const	{
			if     (size() == 0)      return end;
			if     (n == NULL)      n = node_root;
			while  (n->left != end) n = n->left;
			return (n);
		}

		nodePtr		getMax (nodePtr n = NULL) const	{
			if     (size() == 0)     return (end);
			if     (n == NULL)       n = node_root;
			while  (n->right != end) n = n->right;
			return (n);
		}

		nodePtr		getEnd (nodePtr n = NULL) const	{ (void)n; return (end);}


		/* ............. GETTERS / SETTERS .............. */
		nodePtr get_node_root    (void)    const  { return        node_root;    }
		void    set_node_root    (nodePtr n) { node_root    = n;           }
		nodePtr get_node_end     (void)  const    { return        end;    }
		nodePtr get_node_last_inserted  (void)  const    { return        node_last_inserted;    }

		void swap (tree & t) {
			nodePtr     tmp_node_root     = node_root;
			nodePtr     tmp_end           = end;
			Alloc       tmp_alloc         = alloc;
			size_t	    tmp_number_leaves = number_leaves;
			key_compare tmp_comp          = comp;

			node_root     = t.node_root;
			end           = t.end;
			alloc         = t.alloc;
			number_leaves = t.number_leaves;
			comp          = t.comp;


			t.node_root     = tmp_node_root;
			t.end           = tmp_end;
			t.alloc         = tmp_alloc;
			t.number_leaves = tmp_number_leaves;
			t.comp          = tmp_comp;
		};

		/* ================================================================== */
		/* ------------------------------ TODO ------------------------------ */
		/* ================================================================== */

		//void	infixe     (nodePtr ptr) const ; // wtf isinfix
		nodePtr	successeur (nodePtr ptr) const ; // wtf is successeur

		//void		toDelete(nodePtr	node) {
		//nodePtr parent = node->parent;

		//// If node does NOT have children
		//if (node->left == end && node->right == end) {
		//if (node != node_root) {
		//if (parent->left == node) {
		//parent->left = end;
		//}
		//else {
		//parent->right = end;
		//}
		//}
		//else {
		//node_root = end;
		//}
		//}
		//else if (node->left != end && node->right != end) {
		//nodePtr		succ = successeur(node->right);
		//if (node == node_root) {
		//if (succ->right != end && node->right != succ) {
		//succ->parent->left = succ->right;
		//succ->right->parent = succ->parent;
		//}
		//else if (node->right != succ)
		//succ->parent->left = end;

		//if (node->right != end && node->right != succ)
		//node->right->parent = succ;
		//if (node->left != end)
		//node->left->parent = succ;

		//succ->parent = node->parent;
		//succ->left = node->left;
		//if (node->right != succ)
		//succ->right = node->right;
		//node_root = succ;
		//}
		//else {
		//if (succ->right != end && node->right != succ) {
		//succ->parent->left = succ->right;
		//succ->right->parent = succ->parent;
		//}
		//else if (node->right != succ)
		//succ->parent->left = end;

		//if (node->left != end) {
		//node->left->parent = succ;
		//succ->left = node->left;
		//}

		//succ->parent = node->parent;
		//if (node->parent->right == node) {
		//node->parent->right = succ;
		//}
		//else if (node->parent->left == node) {
		//node->parent->left = succ;
		//}
		//if (node->right != succ) {
		//node->right->parent = succ;
		//succ->right = node->right;
		//}
		//}
		//}
		//else {
		//nodePtr	child = (node->left != end) ? node->left : node->right;
		//if (node != node_root) {
		//if (node == parent->left)
		//parent->left = child;
		//else
		//parent->right = child;
		//child->parent = parent;
		//}
		//else {
		//node_root = child;
		//node_root->parent = end;
		//}
		//}
		//alloc.destroy(node);
		//alloc.deallocate(node, 1);
		//node = NULL;
		//}


};

//int main ()
//{
//tree <int, int> t;
//tree <int, int> t2;

//std::cout << "tree size : "<< t.size() << std::endl;

//t.insert(1, 42 );
//t.insert(2, 43 );
//t.insert(5, 48 );
//std::cout << "tree size : "<< t.size() << std::endl;
//std::cout << t.get_node_root()->data << std::endl;
//std::cout << t.get_node_root()->right->data << std::endl;
//std::cout << t.get_node_root()->right->right->data << std::endl;

//std::cout << t.getMin()->key << std::endl;
//std::cout << t.getMax()->key << std::endl;

//t.erase(5);
//std::cout <<	t.getMax()->data << std::endl;
////t.insert_left(-42);
////t.insert_right(42);


////t.get_node_current() = t.get_node_current()->left;

////std::cout << t.get_node_root->data << std::endl;
//std::cout << t.get_node_current()->left->data << std::endl;
//std::cout << t.get_node_current()->right->data << std::endl;
////t.insert_right(42);
//t.set_node_current(t.get_node_current()->left);
//t.insert_left(-56);
//t.insert_right(2);
//std::cout << t.get_node_current()->left->data << std::endl;
//std::cout << t.get_node_current()->right->data << std::endl;
//t.go_root();
//std::cout << t.get_node_current()->left->data << std::endl;
//std::cout << t.get_node_current()->right->data << std::endl;
//std::cout << t.getMin()->data << std::endl;

//node<int, int>* n;
//n = t.find_data(0);
//std::cout << n << std::endl;
//std::cout << n->data << std::endl;

//t.infixe(t.get_node_root());
//}

