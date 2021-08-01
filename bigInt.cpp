#include<bits/stdc++.h>
using namespace std;

//BigInt Class begins
class bigint
{
public:
    vector<int>v;
    int sign;
    bigint()
    {
        sign = 1;
    }
    bigint(long long x)
    {
        *this = x;
    }
    bigint(int x)
    {
        *this = x;
    }
    void operator=(int x)
    {
        sign = 1;
        if(x<0)
        {
            sign = -1;
            x = x*sign;
        }
        fillArray(x);
    }
    void operator=(long long x)
    {
        sign = 1;
        if(x<0)
        {
            sign = -1;
            x = x*sign;
        }
        fillArray(x);
    }
    void operator=(const bigint &x)
    {
        //copy constructor
        sign = x.sign;
        v = x.v;
    }
    void fillArray(long long x)
    {
        while(x)
        {
            v.push_back(x%10);
            x/=10;
        }
    }
    //Addition Here
    bigint add(bigint &x)
    {
        if(sign==x.sign)
        {
            bigint res;
            vector<int>a,b;
            a = v;
            b = x.v;
            res.sign = sign;
            int carry = 0;
            for(int i = 0 ; ; i++)
            {
                if(i>=a.size() && i>=b.size() && !carry)
                {
                    break;
                }
                int cur = carry;
                if(i<a.size())
                {
                    cur+=a[i];
                }
                if(i<b.size())
                {
                    cur+=b[i];
                }
                carry = cur/10;
                res.v.push_back(cur%10);
            }
            return(res);
        }
        bigint y = x;
        y.sign = -x.sign;
        return(*this - (y));
    }
    bigint operator + (long long x)
    {
        bigint tmp(x);
        return(add(tmp));
    }
    bigint operator += (long long x)
    {
        bigint tmp(x);
        return(add(tmp));
    }
    bigint operator + (bigint &b)
    {
        return(add(b));
    }
    bigint operator += (bigint &b)
    {
        return(add(b));
    }
    
    //Subtract Here
    bigint sub(bigint &x)
    {
        if(sign==x.sign)
        {
            if(abs()>=x.abs())
            {
                bigint res;
                res.sign = sign;
                vector<int>a,b;
                a = v;
                b = x.v;
                int carry = 0;
                for(int i = 0 ;  ; i++)
                {
                    if(i>=a.size() && i>=b.size() && !carry)
                    {
                        break;
                    }
                    int cur = -carry;
                    if(i<a.size())
                    {
                        cur += a[i];
                    }
                    if(i<b.size())
                    {
                        cur-=b[i];
                    }
                    carry = 0;
                    if(cur<0)
                    {
                        carry = (-(cur)+9)/10;
                        cur = carry*10 + cur;
                    }
                    res.v.push_back(cur);
                }
                return(res);
            }
            bigint y = x - (*this);
            y.sign = -y.sign;
            return(y);
        }
        bigint y = x;
        y.sign = -x.sign;
        return( (*this) + (y));
    }
    
    bigint operator- (long long x)
    {
        bigint tmp(x);
        return(sub(tmp));
    }
    bigint operator -= (long long x)
    {
        bigint tmp(x);
        return(sub(tmp));
    }
    bigint operator-(bigint &x)
    {
        return(sub(x));
    }
    bigint operator -= (bigint &b)
    {
        return(sub(b));
    }
    
    //Multiplication Here
    bigint mul(bigint &x)
    {
        bigint res;
        res.sign = sign*(x.sign);
        vector<int>a,b;
        a = v;
        b = x.v;
        res.v.push_back(0);
        for(int i = 0 ; i<b.size() ; i++)
        {
            bigint tmp;
            int cur = b[i];
            int carry = 0;
            tmp.sign = res.sign;
            for(int j = 0 ;  ; j++)
            {
                if(j>=a.size() && !carry)
                {
                    break;
                }
                int sm = a[j]*cur + carry;
                tmp.v.push_back(sm%10);
                carry = sm/10;
            }
            res = res + tmp;
        }
        return(res);
    }
    bigint operator* (long long x)
    {
        bigint tmp(x);
        return(mul(tmp));
    }
    bigint operator *= (long long x)
    {
        bigint tmp(x);
        return(mul(tmp));
    }
    bigint operator*(bigint &x)
    {
        return(mul(x));
    }
    bigint operator *= (bigint &b)
    {
        return(mul(b));
    }
    
    //Division Here
    friend pair<bigint,bigint> divmod(const bigint &x1 , const bigint &y1)
    {
        bigint x = x1.abs();
        bigint y = y1.abs();
        bigint res,res2;
        bigint tmp = x;
        res.v.push_back(0);
        while(true)
        {
            if(tmp.abs()<y.abs())
            {
                res2.v = tmp.v;
                break;
            }
            bigint q(2);
            bigint prev(1);
            for(int j = 0 ; ; j++)
            {
                bigint r = q*y;
                if(tmp<r)
                {
                    r = prev*y;
                    tmp = tmp - r;
                    res = res + prev;
                    break;
                }
                prev = q;
                q = q*2;
            }
        }
        res.sign = (x1.sign)*(y1.sign);
        res2.sign = x1.sign;
        return(make_pair(res,res2));
    }
    bigint operator/(const bigint &x) const {
		return(divmod(*this, x).first);
	}
 
	bigint operator%(const bigint &x) const {
		return(divmod(*this, x).second);
	}
    bigint operator/ (long long x)
    {
        bigint tmp(x);
        return(divmod(*this,tmp).first);
    }
    bigint operator /= (long long x)
    {
        bigint tmp(x);
        return(divmod(*this,tmp).first);
    }
    bigint operator% (long long x)
    {
        bigint tmp(x);
        return(divmod(*this,tmp).second);
    }
    bigint operator %= (long long x)
    {
        bigint tmp(x);
        return(divmod(*this,tmp).second);
    }
    
    
    bigint abs() const {
        bigint res = *this;
        res.sign = 1;
        return res;
    }
    bool operator<(const bigint &x) const {
        if (sign != x.sign)
            return sign < x.sign;
        if (v.size() != x.v.size())
            return v.size() * sign < x.v.size() * x.sign;
        for (int i = v.size() - 1; i >= 0; i--)
            if (v[i] != x.v[i])
                return v[i] * sign < x.v[i] * sign;
        return false;
    }
    bool operator>(const bigint &x) const {
        return x < *this;
    }
    bool operator<=(const bigint &x) const {
        return !(x < *this);
    }
    bool operator>=(const bigint &x) const {
        return !(*this < x);
    }
    bool operator==(const bigint &x) const {
        return !(*this < x) && !(x < *this);
    }
    bool operator!=(const bigint &x) const {
        return *this < x || x < *this;
    }
};
int main()
{
    cout<<"BigInt Class in C++\n";
}
