/*
 * @lc app=leetcode.cn id=552 lang=cpp
 *
 * [552] 学生出勤记录 II
 *
 * https://leetcode-cn.com/problems/student-attendance-record-ii/description/
 *
 * algorithms
 * Hard (38.26%)
 * Likes:    55
 * Dislikes: 0
 * Total Accepted:    1.7K
 * Total Submissions: 4.5K
 * Testcase Example:  '1'
 *
 * 给定一个正整数 n，返回长度为 n 的所有可被视为可奖励的出勤记录的数量。 答案可能非常大，你只需返回结果mod 10^9 + 7的值。
 * 
 * 学生出勤记录是只包含以下三个字符的字符串：
 * 
 * 
 * 'A' : Absent，缺勤
 * 'L' : Late，迟到
 * 'P' : Present，到场
 * 
 * 
 * 如果记录不包含多于一个'A'（缺勤）或超过两个连续的'L'（迟到），则该记录被视为可奖励的。
 * 
 * 示例 1:
 * 
 * 
 * 输入: n = 2
 * 输出: 8 
 * 解释：
 * 有8个长度为2的记录将被视为可奖励：
 * "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 * 只有"AA"不会被视为可奖励，因为缺勤次数超过一次。
 * 
 * 注意：n 的值不会超过100000。
 * 
 */

// @lc code=start
class Solution {
	long num;
	vector<string> dict = {"A","L","P"} ;
public:
	/*
	解法一：从长度1开始找，根据长度1的结果生成长度2的结果
	1.没有A；
	2.只有1个A
	3.只有1个L
	4.只有2个连续的L
	可以先找出长度为1的，然后在长度为1的基础上根据上面4个规则找长度为2的
	长度为1： A , L , P
	长度为2： 根据长度1的3种情况增加一个长度，A可以增加为AL , AP ；L可以增加为LA ,LL ,LP ；P可以增加为PA,PL,PP，共8种
	长度为3： 根据长度为2的8种情况增加一个长度，AL=>ALL,ALP ; AP=>APL,APP; LA=>LAL,LAP ; LL=>LLA,LLP ; LP=>LPA,LPL,LPP ; PA=>PAL,PAP ; PL => PLA,PLL,PLP ; PP => PPA , PPL ,PPP 共 19种；
	依次类推，得到长度为n的
	当运行到case n=17时，超时
	*/
	/*
    int checkRecord(int n) {
		vector<string> dict = {"A","L","P"} ;
		unordered_set<int> hasA({0});
		if(n == 1) return dict.size();


		vector<vector<string> > dp(n);
		dp.push_back(dict);

		for(int i = 1 ; i <n ; ++ i) {
			unordered_set<int> nextA ;
			vector<string> one ; 
			for(int j = 0 ; j < dp.back().size() ; ++ j) {
				//不包含A
				for(auto d : dict) {
					string str = dp.back()[j]	;

					if(hasA.find(j) != hasA.end() && d == "A"){
						continue;
					}
					//记录包含A的位置
					else if((hasA.find(j) != hasA.end() && d != "A" )|| (hasA.find(j) == hasA.end() && d == "A")) {
						//判断是否是LL
						if(str.size()>1 && str.back() == 'L' && str[str.size()-2] == 'L' && d == "L" ) {
							continue;
						}

						nextA.emplace(one.size());
					}
					else if(hasA.find(j) == hasA.end()) {
						//判断是否是LL
						if(str.size()>1 && str.back() == 'L' && str[str.size()-2] == 'L' && d == "L" ) {
							continue;
						}
					}

					str.append(d);		
					one.push_back(str);
				}
			}
			hasA = nextA;
			dp.push_back(one);
		}
		
		for(auto one : dp.back()) {
			cout << one << endl;
		}
		return dp.back().size()%1000000007;
	}
	*/

	/*
	解法二：递归
	*/
	/*
    int checkRecord(int n) {

		if(n == 1) return dict.size();

		for(auto one : dict) {
			bool hasA = false ;
			if(one == "A") hasA = true;
			getNext(one,n,hasA);
		}

		return num%1000000007;
	}
	*/
	void getNext(string one , int n , bool hasA) {
//		cout << one << "," << n << "," << (int)hasA << endl;
		//已经包含字符‘A'，可选只有P，L，但不能允许2个L连续
		if(hasA == true)
		{
			//已经是最后一个字符，判断L能否增加上去
			if(one.size() == (n-1)) {
				//可以加P或者L
				if(one.size() == 1 || !(one.size()>1 && one.back() == 'L' && one[one.size()-2] == 'L')) {
					num += 2;
				}
				//只能加P
				else {
					num += 1;
				}
			}
			else {
				one.append("P");
				getNext(one,n,hasA);
				one.pop_back();

				if(one.size() == 1 || !(one.size()>1 && one.back() == 'L' && one[one.size()-2] == 'L')) {
//					cout <<"get L : " << one << endl;
					one.append("L");
					getNext(one,n,hasA);
				}
			}
		}
		//不包含字符A，可选A，P，L，只需要判断是否有2个连续的L
		else
		{
			if(one.size() == (n-1)) {
				if(one.size()>1 && one.back() == 'L' && one[one.size()-2] == 'L') {
					//只能加P，A
					num += 2;
				}
				//可以加A，P，L
				else {
					num += 3;
				}
			}
			else {
				one.append("P");
				getNext(one,n,hasA);
				one.pop_back();

				one.append("A");
				getNext(one,n,true);
				one.pop_back();


				if(one.size() == 1 || !(one.size()>1 && one.back() == 'L' && one[one.size()-2] == 'L')) {
					one.append("L");
					getNext(one,n,hasA);
				}
			}
		}

	}


	/*
	解法三：动态规划
	用2个维度来定义状态，定义第一个维度i代表长度为i，第二个维度按照是否包含A区分，其中包含A的再分别按以P结尾，以A结尾，以L结尾，以LL结尾进行区分。不包含A的也分别按以P结尾 ，以L结尾，以LL结尾进行区分，得到定义
	dp[i][0]=长度为i，包含A且以P结尾的记录数
	dp[i][1]=长度为i，包含A且以A结尾的记录数
	dp[i][2]=长度为i，包含A且以L结尾的记录数
	dp[i][3]=长度为i，包含A且以LL结尾的记录数
	dp[i][4]=长度为i，不包含A且以P结尾的记录数
	dp[i][5]=长度为i，不包含A且以L结尾的记录数
	dp[i][6]=长度为i，不包含A且以LL结尾的记录数
	result = sum(dp[i][0]....dp[i][6])
	做公式递推:
	dp[i+1][0]=dp[i][0] +dp[i][1] +dp[i][2]+ dp[i][3] 
	dp[i+1][1]=dp[i][4]+dp[i][5]+dp[i][6]
	dp[i+1][2]=dp[i][0] + dp[i][1] 
	dp[i+1][3]=dp[i][2]
	dp[i+1][4]=dp[i][4]+dp[i][5]+dp[i][6]
	dp[i+1][5]=dp[i][4]
	dp[i+1][6]=dp[i][5]
	result = sum(dp[i+1][0]....dp[i+1][6])
	*/
	int checkRecord(int n) {
		if(n < 1) return 0 ;
		vector<vector<unsigned long long>> dp(n,vector<unsigned long long>(7,0)) ;

		//初始化n=1的情况
		dp[0][0] = 0;
		dp[0][1] = 1;
		dp[0][2] = 0;
		dp[0][3] = 0;
		dp[0][4] = 1;
		dp[0][5] = 1;
		dp[0][6] = 0;

		int mode = 1000000007 ;
		for(int i = 1 ; i < n ; ++i) {
			dp[i][0] = (dp[i-1][0] +dp[i-1][1] +dp[i-1][2]+ dp[i-1][3])%mode ;
			dp[i][1] = (dp[i-1][4]+dp[i-1][5]+dp[i-1][6])%mode ;
			dp[i][2] = (dp[i-1][0] + dp[i-1][1])%mode ;
			dp[i][3] = (dp[i-1][2])%mode ;
			dp[i][4] = (dp[i-1][4]+dp[i-1][5]+dp[i-1][6])%mode ;
			dp[i][5] = (dp[i-1][4])%mode ;
			dp[i][6] = (dp[i-1][5])%mode ;
		}

		unsigned long long result = 0 ;
		for(auto num : dp[n-1]) {
			result += num ;
			result %= mode ;
		}

		return result ;
	}

	/*
	解法四：解法三的空间优化，计算dp[i+1]只需要dp[i]的值即可，所以不需要7*n的空间
	*/
	int checkRecord(int n) {
		if(n < 1) return 0 ;
		vector<unsigned long long> pre(7,0) ;
		vector<unsigned long long> cur(7,0) ;

		//初始化n=1的情况
		pre[0] = 0;
		pre[1] = 1;
		pre[2] = 0;
		pre[3] = 0;
		pre[4] = 1;
		pre[5] = 1;
		pre[6] = 0;

		cur = pre ;

		
		int mode = 1000000007 ; 
		//大数取模的巧算：(a+b)%c = (a%c+b%c)%c，同时可以避免大数相加带来的溢出
		for(int i = 1 ; i < n ; ++i) {
			cur[0] = (pre[0] %mode+pre[1] %mode+pre[2]%mode+ pre[3]%mode)%mode ;
			cur[1] = (pre[4]%mode+pre[5]%mode+pre[6]%mode)%mode ;
			cur[2] = (pre[0]%mode + pre[1]%mode)%mode ;
			cur[3] = (pre[2])%mode ;
			cur[4] = (pre[4]%mode+pre[5]%mode+pre[6]%mode)%mode ;
			cur[5] = (pre[4])%mode ;
			cur[6] = (pre[5])%mode ;
			pre = cur;
		}

		unsigned long long result = 0 ;
		for(auto num : cur) {
			result += num ;
			result %= mode ;
		}

		return result ;
	}


	/*
	社区高赞解法，思路一样，状态做了精简
	*/
	int checkRecord(int n) {
		int m = 1000000007;
		int *A = new int [n];
		int *P = new int [n];
		int *L = new int [n];

		P[0] = 1;
		L[0] = 1;
		L[1] = 3;
		A[0] = 1;
		A[1] = 2;
		A[2] = 4;

		if(n == 1) return 3;

		for(int i = 1; i < n; i++)
		{
			A[i - 1] %= m;
			P[i - 1] %= m;
			L[i - 1] %= m;

			P[i] = ((A[i - 1] + P[i - 1]) % m + L[i - 1]) % m;

			if(i > 1) L[i] = ((A[i - 1] + P[i - 1]) % m + (A[i - 2] + P[i - 2]) % m) % m;

			if(i > 2) A[i] = ((A[i - 1] + A[i - 2]) % m + A[i - 3]) % m;
		}

		return ((A[n - 1] % m + P[n - 1] % m) % m + L[n - 1] % m) % m;
	}


};
// @lc code=end
/*
   int main(char *argv[],int argc) {
   Solution a;

   a.checkRecord(atoi(argv[1]));
   }
 */
