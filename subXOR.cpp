#include<bits/stdc++.h>
using namespace std;

struct node{
	int leftc;
	int rightc;
	struct node *left;
	struct node *right;
};

node *insert(node *root, int n, int level){

	if(level == -1) return root;

	int x = ((n >> level) & 1);

	if(x){
		root->rightc++;
		if(root->right == NULL){
			root->right = (node *)malloc(sizeof(node));
			root->right->leftc = root->right->rightc = 0;
		}
		root->right = insert(root->right, n, level-1);
	}
	else{
		root->leftc++;

		if(root->left == NULL){
			root->left = (node *)malloc(sizeof(node));
			root->left->leftc = root->left->rightc = 0;
		}
		root->left = insert(root->left, n, level-1);
	}

	return root;

}


int query(node *root, int n, int k, int level){

	if(level == -1 || root == NULL) return 0;

	int p = ((n >> level) & 1);
	int q = ((k >> level) & 1);

	if(q){
		if(p == 0) return (root->leftc + query(root->right, n, k, level - 1));
		else return (root->rightc + query(root->left, n, k, level-1));
	}
	else{
		if(!p && root->left) return query(root->left, n, k, level - 1);
		else if(root->right) return query(root->right, n, k, level - 1);
	}

}


int main(){

	int t;
	cin >> t;

	while(t--){
		
		node *root;

		root = (node *)malloc(sizeof(node));
		root->left = root->right = NULL;
		root->leftc = root->rightc = 0;
        // exit(0);
		root = insert(root, 0, 20);
        // exit(0);

		int n, k, x, ans = 0, q = 0, level = 20, p = 0;

		cin >> n >> k;

		for(int i = 0;i<n;i++){
			cin >> x;

			q = p^x;
            // exit(0);
			ans += query(root, q, k, 20);
            //exit(0);

			root = insert(root, q, 20);
			p = q;
		}

		cout << ans << endl;

	}


	return 0;
}