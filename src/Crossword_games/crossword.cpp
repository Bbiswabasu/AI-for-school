#include<bits/stdc++.h>
using namespace std;


const int M=30;
char ar[M+5][M+5];
pair<int,int> edges[M+5][M+5][2]; 
int vis[M+5][M+5]; 
int len[M+5][M+5][2]; 
vector<int> notdom[M+5][M+5][2]; 

vector<pair<int,int>> graph[M+5][M+5][2]; 
int szbag;
deque <pair<pair<pair<int,int>,int>,pair<pair<int,int>,int>>> q;
string bag[12][250]={
	{},
	{},
	{},
	{"act", "add", "age", "ago", "air", "all", "and", "any", "are", "arm", "art", "ask", "bad", "bag", "bar", "bed", "big", "bit", "box", "boy", "but", "buy", "bye", "can", "car", "cup", "cut", "dad", "day", "did", "die", "dog", "eat", "end", "eye", "far", "few", "fly", "for", "fun", "gas", "get", "god", "got", "gun", "guy", "had", "has", "hen", "her", "hey", "him", "his", "hit", "hot", "how", "its", "job", "key", "kid", "law", "lay", "leg", "let", "lie", "lot", "low", "man", "may", "men", "met", "mom", "mrs", "new", "nor", "not", "now", "nun", "off", "oft", "oil", "old", "one", "our", "out", "own", "pay", "per", "put", "red", "run", "saw", "say", "sea", "see", "set", "hex", "she", "sir", "sit", "six", "son", "tax", "ten", "the", "too", "top", "try", "two", "use", "war", "was", "way", "who", "why", "win", "yes", "yet", "you"},
	{"also", "area", "away", "baby", "back", "ball", "bank", "base", "beat", "best", "bill", "blue", "body", "book", "born", "both", "call", "card", "care", "case", "cell", "city", "cold", "come", "cost", "dark", "data", "dead", "deal", "deep", "door", "down", "draw", "drop", "drug", "each", "east", "easy", "edge", "else", "even", "ever", "face", "fact", "fail", "fall", "fast", "fear", "feel", "fill", "film", "find", "fine", "fire", "firm", "fish", "five", "food", "foot", "form", "four", "free", "from", "full", "fund", "game", "girl", "give", "goal", "good", "grow", "hair", "half", "hand", "hang", "hard", "have", "head", "hear", "heat", "help", "here", "high", "hold", "home", "hope", "hour", "huge", "idea", "into", "item", "join", "just", "keep", "kill", "kind", "know", "land", "last", "late", "lead", "left", "less", "life", "like", "line", "list", "live", "long", "look", "lose", "loss", "love", "main", "make", "many", "mean", "meet", "mind", "mint", "miss", "more", "most", "move", "much", "must", "name", "near", "need", "news", "next", "nice", "none", "note", "once", "only", "onto", "open", "over", "page", "pain", "part", "pass", "past", "pick", "plan", "play", "poor", "pull", "push", "race", "rate", "read", "real", "rest", "rich", "rise", "risk", "road", "rock", "role", "room", "rule", "safe", "same", "save", "seat", "seek", "seem", "sell", "send", "shot", "show", "side", "sign", "sing", "site", "size", "skin", "some", "song", "soon", "sort", "star", "stay", "step", "stop", "such", "sure", "take", "talk", "task", "team", "tell", "tend", "term", "test", "than", "that", "them", "then", "they", "this", "thus", "time", "town", "tree", "trip", "true", "turn", "type", "unit", "upon", "very", "view", "vote", "wait", "walk", "wall", "want", "wear", "week", "well", "west", "what", "when", "whom", "wide", "wife", "will", "wind", "wish", "with", "word", "work", "yard", "yeah", "year", "your"},
	{"above", "admit", "adult", "after", "again", "agent", "agree", "ahead", "allow", "alone", "along", "among", "apply", "argue", "avoid", "batch", "begin", "black", "blood", "board", "break", "bring", "build", "carry", "catch", "cause", "chair", "check", "child", "civil", "claim", "class", "clear", "close", "coach", "color", "could", "court", "cover", "crime", "death", "dream", "drive", "early", "eight", "enjoy", "enter", "event", "every", "exist", "field", "fight", "final", "first", "floor", "focus", "force", "front", "glass", "great", "green", "group", "guess", "happy", "heart", "heavy", "hotel", "house", "human", "image", "issue", "large", "later", "laugh", "learn", "least", "leave", "legal", "level", "light", "local", "major", "maybe", "media", "might", "model", "money", "month", "mouth", "movie", "music", "never", "night", "north", "occur", "offer", "often", "order", "other", "owner", "paper", "party", "peace", "phone", "piece", "place", "plant", "point", "power", "price", "prove", "quilt", "quite", "radio", "raise", "range", "reach", "ready", "right", "scene", "score", "sense", "serve", "seven", "shake", "share", "shoot", "short", "since", "skill", "small", "smile", "sound", "south", "cout<<" ";", "speak", "spend", "sport", "staff", "stage", "stand", "start", "state", "still", "stock", "store", "story", "study", "stuff", "style", "table", "teach", "thank", "their", "there", "these", "thing", "think", "third", "those", "three", "throw", "today", "total", "tough", "trade", "treat", "trial", "truth", "under", "until", "value", "visit", "voice", "watch", "water", "where", "which", "while", "white", "whole", "whose", "woman", "world", "worry", "would", "write", "wrong", "young"},
	{"across", "action", "affect", "agency", "almost", "always", "amount", "animal", "answer", "anyone", "appear", "around", "arrive", "artist", "assume", "attack", "author", "become", "before", "behind", "better", "beyond", "bright", "budget", "camera", "cancer", "career", "center", "chance", "change", "charge", "choice", "choose", "church", "common", "couple", "course", "create", "debate", "decade", "decide", "degree", "design", "detail", "dinner", "doctor", "during", "effect", "effort", "either", "energy", "enough", "entire", "expect", "expert", "factor", "family", "father", "figure", "finger", "finish", "follow", "forget", "former", "friend", "future", "garden", "grease", "ground", "growth", "happen", "health", "height", "impact", "indeed", "inside", "itself", "lawyer", "leader", "letter", "likely", "listen", "little", "manage", "market", "matter", "member", "memory", "method", "middle", "minute", "modern", "moment", "mother", "myself", "nation", "nature", "nearly", "notice", "number", "office", "option", "others", "parent", "people", "period", "person", "player", "police", "policy", "pretty", "public", "rather", "really", "reason", "recent", "record", "reduce", "region", "relate", "remain", "remove", "report", "result", "return", "reveal", "school", "season", "second", "senior", "series", "annual", "should", "simple", "simply", "single", "sister", "social", "source", "speech", "spring", "street", "strong", "suffer", "summer", "system", "theory", "though", "threat", "toward", "travel", "victim", "weapon", "weight", "window", "within", "wonder", "worker", "writer"},
	{"account", "address", "against", "already", "another", "article", "because", "believe", "benefit", "between", "billion", "brother", "capital", "central", "century", "certain", "channel", "citizen", "clearly", "college", "company", "compare", "concern", "contain", "control", "country", "culture", "current", "defense", "despite", "develop", "discuss", "disease", "economy", "evening", "exactly", "example", "explain", "federal", "feeling", "finally", "foreign", "forward", "general", "herself", "himself", "history", "however", "hundred", "husband", "imagine", "improve", "include", "instead", "involve", "january", "kitchen", "machine", "manager", "measure", "medical", "meeting", "mention", "message", "million", "mission", "morning", "natural", "network", "nothing", "officer", "outside", "partner", "patient", "pattern", "perform", "perhaps", "picture", "planner", "popular", "prepare", "present", "prevent", "private", "problem", "process", "produce", "product", "program", "project", "protect", "provide", "purpose", "quality", "quickly", "reality", "realize", "receive", "reflect", "require", "respond", "science", "section", "serious", "service", "several", "similar", "society", "soldier", "someone", "special", "station", "student", "subject", "success", "suggest", "support", "surface", "teacher", "thermal", "thought", "through", "tonight", "trouble", "usually", "various", "western", "whether", "without"},
	{"Congress", "Democrat", "activity", "actually", "although", "analysis", "anything", "approach", "attorney", "audience", "behavior", "building", "business", "campaign", "computer", "consider", "consumer", "continue", "cultural", "customer", "daughter", "decision", "describe", "director", "discover", "division", "economic", "election", "employee", "everyone", "evidence", "exercise", "hospital", "identify", "increase", "indicate", "industry", "interest", "language", "magazine", "maintain", "majority", "marriage", "material", "military", "movement", "national", "official", "painting", "personal", "physical", "politics", "position", "positive", "possible", "practice", "pressure", "probably", "property", "question", "recently", "remember", "research", "resource", "response", "security", "shoulder", "somebody", "southern", "specific", "standard", "strategy", "suddenly", "thousand", "together", "training", "violence", "whatever", "yourself"},
	{"agreement", "attention", "authority", "available", "beautiful", "candidate", "certainly", "challenge", "character", "community", "condition", "determine", "different", "difficult", "direction", "education", "establish", "everybody", "executive", "financial", "important", "interview", "knowledge", "necessary", "newspaper", "operation", "political", "president", "professor", "recognize", "religious", "represent", "scientist", "situation", "something", "sometimes", "statement", "structure", "treatment"},
	{"adaptation", "collection", "commercial", "conference", "democratic", "difference", "discussion", "especially", "everything", "experience", "flamboyant", "generation", "government", "horizontal", "hypothesis", "individual", "investment", "management", "particular", "passionate", "population", "production", "skateboard", "successful", "technology", "television", "themselves", "throughout", "understand"},
	{"environment", "information", "institution", "interesting", "opportunity", "participant", "performance", "significant", "traditional"}
};

int bagct[12]={0,0,0,120,240,190,160,130,80,40,30,10};
int rebag[12][50];
pair<int,int> moves[4]={{0,1},{1,0},{0,-1},{-1,0}};
int fac[M+5];
int dist[M+5];
int n;
vector<pair<pair<int,int>,int> > nodes;

void init(int n)
{
	memset(vis,0,sizeof(vis));
	for(int i=0;i<2*n;i++)
	{
		for(int j=0;j<2*n;j++)
		{
			ar[i][j]='#';
		}
	}

	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<n+1;j++)
		{
			ar[i][j]='.';
			if((i&1)==0 and (j&1)==0)
			{
				ar[i][j]='#';
			}
		}
	}
}

void formgrid(int n,int uplen)
{
	int md=1<<(uplen);
	for(int i=1;i<n+1;i++)
	{
		if((i&1))
		{
			int val;
			int len;
			int pos=1;
			while(pos<=n)
			{
				while(1)
				{
				 	val=rand()%(md)+1;
					for(int j=0;j<uplen+2;j++)
					{
						if(val<=dist[j])
						{
							len=j;
							break;
						}
					}			
					if(len>2 and len<=uplen)
					{
						break;
					}
				}
				int pl;
				if(pos==1)
					pl=rand()%(uplen-3);
				else
				{
					pl=rand()%(uplen-4);
				}
				for(int j=pos;j<pos+pl;j++)
				{
					ar[i][j]='#';
				}
				for(int j=pl+pos;j<pl+pos+len;j++)
				{
					ar[i][j]='.';
				}		
				ar[i][pl+pos+len]='#';	
				pos+=pl+len+1;
				ar[i][n+1]='#';			
			}

		}
	}

}

void printgrid(int n)
{
	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<n+1;j++)
		{
			cout<<ar[i][j];cout<<" ";;
		}
		cout<<"\n";
	}	
	cout<<"\n";
}

void transpose(int n)
{
	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<i;j++)
		{
			swap(ar[i][j],ar[j][i]);
		}
	}
	
}

void remove2(int n)
{
	for(int i=1;i<n+2;i++)
	{
		if((i&1)==0)
		{
			continue;
		}
		int ct=0;
		for(int j=1;j<n+2;j++)
		{
			if(ar[i][j]=='.')
				ct+=1;
			else
			{
				if(ct==2)
				{
					if((j&1))
					{
						ar[i][j-1]='#';
					}
					else
					{
						ar[i][j-2]='#';
					}
				}
				ct=0;
			}
		}
	}
}
void remove1(int n)
{
	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<n+1;j++)
		{
			int cur=0;
			for(int k=0;k<4;k++)
			{
				if(ar[i+moves[k].first][j+moves[k].second]=='#')
					cur++;
			}
			if(cur==4)
			{
				ar[i][j]='#';
			}			
		}
	}	
}

void distribution(int n,int uplen)
{
	fac[0]=1;
	for(int i=1;i<uplen+1;i++)
	{
		fac[i]=i*fac[i-1];
	}
	cout<<"\n";
	dist[0]=1;
	for(int i=1;i<uplen+1;i++)
	{
		dist[i]=fac[uplen]/(fac[i]*fac[uplen-i])+dist[i-1];
	}
	cout<<"\n";
}



void cspify(int n)
{
	for(int i=1;i<n+2;i++)
	{
		int ct=0;
		for(int j=1;j<n+2;j++)
		{
			if(ar[i][j]=='.')
			{
				ct++;
			}
			else
			{
				if(ct>1)
				{
					nodes.push_back({{i,j-ct},0});
					len[i][j-ct][0]=ct;
				}
				ct=0;
			}
		}
	}
	for(int j=1;j<n+2;j++)
	{
		int ct=0;
		for(int i=1;i<n+2;i++)
		{
			if(ar[i][j]=='.')
			{
				ct++;
			}
			else
			{
				if(ct>1)
				{
					nodes.push_back({{i-ct,j},1});
					len[i-ct][j][1]=ct;
				}
				ct=0;
			}
		}
	}

	int m=nodes.size();


	for(int i=0;i<m;i++)
	{

		auto cur=nodes[i];
		int x=cur.first.first;
		int y=cur.first.second;
		int t=cur.second;

		int ty=y;
		int tx=x;
		if(t==1)
		{
			while(ar[tx][ty]=='.')
			{
				if(ar[tx][ty-1]=='.' or ar[tx][ty+1]=='.')
				{
					edges[tx][ty][1]={x,y};
					vis[tx][ty]=1;
				}
				tx++;
			}
		}

		if(t==0)
		{
			while(ar[tx][ty]=='.')
			{
				if(ar[tx-1][ty]=='.' or ar[tx+1][ty]=='.')
				{
					edges[tx][ty][0]={x,y};
					vis[tx][ty]=1;
				}
				ty++;
			}
		}

	}

	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<n+1;j++)
		{
			if(vis[i][j])
			{
				auto ph=edges[i][j][0];
				auto pv=edges[i][j][1];

				graph[ph.first][ph.second][0].push_back(pv);
				graph[pv.first][pv.second][1].push_back(ph);

				q.push_back({{{ph.first,ph.second},0},{{pv.first,pv.second},1}});
				q.push_back({{{pv.first,pv.second},1},{{ph.first,ph.second},0}});
			}
		}
	}
}



void printgraph(int n)
{
	int i,j,k;
	for(auto node:nodes)
	{
		i=node.first.first;
		j=node.first.second;
		k=node.second;

		cout<<i;cout<<"-";
		cout<<j;cout<<"-";
		cout<<k;cout<<"\n";
		for(auto x: graph[i][j][k])
		{
			cout<<x.first;cout<<"-";
			cout<<x.second;cout<<" ";;
		}
		cout<<"\n";
	}
}



void choose(int n)
{
	for(int i=3;i<n+1;i++)
	{
		int tp[bagct[i]];
		for(int j=0;j<bagct[i];j++)
		{
			tp[j]=j;
		}
		random_shuffle(tp,tp+bagct[i]);
		for(int j=0;j<szbag;j++)
		{
			rebag[i][j]=tp[j];
			cout<<(bag[i][tp[j]]);
			cout<<" ";;
		}
		cout<<"\n";
	}
	cout<<"\n";
}

void printbag(int n)
{
	int i,j,k;
	for(auto node:nodes)
	{
		i=node.first.first;
		j=node.first.second;
		k=node.second;

		cout<<i;cout<<"-";
		cout<<j;cout<<"-";
		cout<<k;cout<<"\n";
		int length=len[i][j][k];

		vector<int> temp;
		int flag;
		for(int cur=0;cur<szbag;cur++)
		{
			flag=0;
			for(auto x: notdom[i][j][k])
			{
				if(cur==x)
				{
					flag=1;
				}
			}	
			if(!flag)
			{
				temp.push_back(cur);
			}					
		}
		for(auto x: temp)
		{
			int pos=rebag[length][x];
			string s=bag[length][pos];
			cout<<s;cout<<" ";;
		}
		cout<<"\n";
	}
}

bool revise(pair<pair<int,int>,int> fp,pair<pair<int,int>,int> sp)
{
	int fx=fp.first.first;
	int fy=fp.first.second;
	int fbin=fp.second;

	int sx=sp.first.first;
	int sy=sp.first.second;
	int sbin=sp.second;

	int flength=len[fx][fy][fbin];
	int slength=len[sx][sy][sbin];

	int intx;
	int inty;

	if(fbin==0)
	{
		intx=fx;
		inty=sy;
	}
	else
	{
		intx=sx;
		inty=fy;
	}

	int gf=0;
	for(int i=0;i<szbag;i++)
	{
		int fpos=rebag[flength][i];
		string fcur=bag[flength][fpos];
		int top=0;
		for(auto x: notdom[fx][fy][fbin])
		{
			if(x==i)
			{
				top=1;
			}
		}
		if(top)
		{
			continue;
		}

		int flag=0;
		if(fbin==0)
		{
			for(int j=0;j<szbag;j++)
			{
				int top=0;
				for(auto x: notdom[sx][sy][sbin])
				{
					if(x==j)
					{
						top=1;
					}
				}
				if(top)
				{
					continue;
				}
				int spos=rebag[slength][j];
				string scur=bag[slength][spos];
				if(fcur[inty-fy]==scur[intx-sx])
				{
					flag=1;
				}
			}			
		}
		else
		{
			for(int j=0;j<szbag;j++)
			{
				int top=0;
				for(auto x: notdom[sx][sy][sbin])
				{
					if(x==j)
					{
						top=1;
					}
				}
				if(top)
				{
					continue;
				}
				int spos=rebag[slength][j];
				string scur=bag[slength][spos];
				if(fcur[intx-fx]==scur[inty-sy])
				{
					flag=1;
				}
			}						
		}
		if(!flag)
		{
			gf=1;
			notdom[fx][fy][fbin].push_back(i);

		}
	}
	return gf;
}

void ac3()
{
	while(!q.empty())
	{
		auto tp=q.front();
		q.pop_front();
		auto fp=tp.first;
		auto sp=tp.second;
		if(revise(fp,sp))
		{
			int x=fp.first.first;
			int y=fp.first.second;
			int bin=fp.second;
			for(int i=0;i<graph[x][y][bin].size();i++)
			{
				auto val=graph[x][y][bin][i];
				if(val==sp.first)
				{
					continue;
				}

				// int valx=val.first.first;
				// int valy=val.first.second;
				// int valbin=val.second;
				q.push_back({{val,1-bin},fp});
			}
		}
	}
}

void findarc()
{
	cout<<"Find the missing constraint for the above crossword grid";cout<<"\n";
	int numofarcs=q.size();
	int temp=rand()%numofarcs;
	// auto cur=q[temp];
	int i=0;
	pair<pair<pair<int,int>,int>,pair<pair<int,int>,int> > ans;
	for(auto cur: q)
	{
		if(i!=temp and (i&1)==(temp&1 ))
		{
			cout<<cur.first.first.first;cout<<"-";
			cout<<cur.first.first.second;cout<<"-";
			cout<<cur.first.second;cout<<" ";;

			cout<<cur.second.first.first;cout<<"-";
			cout<<cur.second.first.second;cout<<"-";
			cout<<cur.second.second;cout<<" ";;
			cout<<"\n";
		}
		else
		{
			ans=cur;
		}
		i++;
	}


	cout<<"Ans:\n";

	// i=temp;
	cout<<ans.first.first.first;cout<<"-";
	cout<<ans.first.first.second;cout<<"-";
	cout<<ans.first.second;cout<<" ";;

	cout<<ans.second.first.first;cout<<"-";
	cout<<ans.second.first.second;cout<<"-";
	cout<<ans.second.second;cout<<" ";;
	cout<<"\n";

}


void fillv1()
{
	cout<<"What all nodes are more constrained than others?";
	cout<<"\n";
	int numofnodes=nodes.size();
	int temp=rand()%numofnodes;
	auto cur=nodes[temp];

	int x=cur.first.first;
	int y=cur.first.second;
	int t=cur.second;
	int ct=len[x][y][t];
	string s=bag[ct][rand()%30];
	if(t==0)
	{
		for(int i=0;i<ct;i++)
		{
			ar[x][y+i]=s[i];
		}
	}
	else
	{
		for(int i=0;i<ct;i++)
		{
			ar[x+i][y]=s[i];
		}
	}
	for(auto cur:graph[x][y][t])
	{
		cout<<cur.first;cout<<"-";
		cout<<cur.second;cout<<" ";;
		cout<<"\n";
	}

}

int main() 
{
	int a,b,c,d,e,q,h,i,j,k,m,n,n1,n2,n3;
	srand(time(NULL));
	cin>>n;
	init(n);
	int uplen=sqrt(n)+3;
	distribution(n,uplen);
	formgrid(n,uplen);
	szbag=20;

	remove2(n);
	// printgrid(n);

	transpose(n);
	// printgrid(n);

	remove2(n);
	// printgrid(n);

	transpose(n);
	// printgrid(n);
	
	remove1(n);
	// printgrid(n);

	if(rand()%2)
	{
		transpose(n);
	}
	printgrid(n);

	cspify(n);
	printgraph(n);

	findarc();

	fillv1();
	printgrid(n);



	choose(n);

	ac3();
	cout<<"\n";
	printbag(n);
	printgrid(n);
}