# Terraform Infrastructure

Infrastructure as Code using Terraform for AWS deployment.

## Features

- VPC with public subnets across multiple availability zones
- ECR repository for Docker images
- Automated image lifecycle management
- Tagged resources for cost tracking
- Remote state management support

## Usage

### Initial Setup

```bash
# Initialize Terraform (local backend)
terraform init

# Initialize with remote S3 backend
terraform init \
  -backend-config="bucket=my-terraform-state-bucket" \
  -backend-config="key=build-systems/terraform.tfstate" \
  -backend-config="region=us-east-1"

# Plan changes
terraform plan

# Apply changes
terraform apply

# Destroy infrastructure
terraform destroy
```

## Configuration

### Environment Variables

Configure Terraform using environment variables (recommended for CI/CD):

```bash
# AWS Credentials (use IAM roles in production)
export AWS_ACCESS_KEY_ID="your-access-key"
export AWS_SECRET_ACCESS_KEY="your-secret-key"
export AWS_DEFAULT_REGION="us-east-1"

# Terraform Backend
export TF_STATE_BUCKET="my-terraform-state-bucket"
export TF_STATE_KEY="build-systems/terraform.tfstate"
export TF_STATE_REGION="us-east-1"
```

### Variables File

Create a `terraform.tfvars` file to customize variables:

```hcl
aws_region         = "us-east-1"
environment        = "production"
app_name           = "build-systems"
availability_zones = ["us-east-1a", "us-east-1b", "us-east-1c"]
vpc_cidr           = "10.0.0.0/16"
```

**IMPORTANT**: Never commit `terraform.tfvars` with sensitive data!

## State Management

### Remote Backend (Recommended)

For production and team environments, use remote state with S3:

1. **Create S3 bucket for state**:
   ```bash
   aws s3 mb s3://my-terraform-state-bucket
   aws s3api put-bucket-versioning \
     --bucket my-terraform-state-bucket \
     --versioning-configuration Status=Enabled
   ```

2. **Enable encryption**:
   ```bash
   aws s3api put-bucket-encryption \
     --bucket my-terraform-state-bucket \
     --server-side-encryption-configuration '{
       "Rules": [{
         "ApplyServerSideEncryptionByDefault": {
           "SSEAlgorithm": "AES256"
         }
       }]
     }'
   ```

3. **Update backend configuration** in `main.tf`:
   ```hcl
   terraform {
     backend "s3" {
       bucket         = "my-terraform-state-bucket"
       key            = "build-systems/terraform.tfstate"
       region         = "us-east-1"
       encrypt        = true
       dynamodb_table = "terraform-locks"  # Optional: for state locking
     }
   }
   ```

4. **Create DynamoDB table for state locking** (optional but recommended):
   ```bash
   aws dynamodb create-table \
     --table-name terraform-locks \
     --attribute-definitions AttributeName=LockID,AttributeType=S \
     --key-schema AttributeName=LockID,KeyType=HASH \
     --billing-mode PAY_PER_REQUEST
   ```

### Local Backend

For development and testing:

```hcl
terraform {
  backend "local" {
    path = "terraform.tfstate"
  }
}
```

## Security Best Practices

### Credentials Management

- ✅ **Never commit credentials** to version control
- ✅ Use **IAM roles** for EC2/ECS instances
- ✅ Use **OIDC** for GitHub Actions authentication
- ✅ Store secrets in **AWS Secrets Manager** or **Parameter Store**
- ✅ Use **environment variables** for temporary credentials

### State File Security

- ✅ Enable **encryption** on S3 bucket
- ✅ Enable **versioning** for state recovery
- ✅ Use **state locking** with DynamoDB
- ✅ Restrict **S3 bucket access** with IAM policies
- ✅ Never commit `.tfstate` files

### Sensitive Variables

Mark sensitive variables in `variables.tf`:

```hcl
variable "database_password" {
  description = "Database password"
  type        = string
  sensitive   = true
}
```

## CI/CD Integration

### GitHub Actions Example

```yaml
- name: Setup Terraform
  uses: hashicorp/setup-terraform@v3
  with:
    terraform_version: 1.6.0

- name: Configure AWS Credentials
  uses: aws-actions/configure-aws-credentials@v4
  with:
    role-to-assume: arn:aws:iam::ACCOUNT:role/GitHubActions
    aws-region: us-east-1

- name: Terraform Init
  run: |
    cd infra/terraform
    terraform init \
      -backend-config="bucket=${{ secrets.TF_STATE_BUCKET }}" \
      -backend-config="key=build-systems/terraform.tfstate" \
      -backend-config="region=us-east-1"

- name: Terraform Plan
  run: terraform plan -out=tfplan

- name: Terraform Apply
  if: github.ref == 'refs/heads/main'
  run: terraform apply -auto-approve tfplan
```

## Resources Created

### Networking
- **VPC**: Virtual Private Cloud with custom CIDR
- **Subnets**: Public subnets across multiple AZs
- **Internet Gateway**: For external connectivity
- **Route Tables**: Routing configuration

### Container Registry
- **ECR Repository**: Docker image registry
- **Lifecycle Policy**: Automatic cleanup of old images (keeps last 10)

### Outputs
- `vpc_id` - VPC identifier
- `public_subnet_ids` - List of subnet IDs  
- `ecr_repository_url` - Docker registry URL

## Common Commands

```bash
# Format code
terraform fmt

# Validate configuration
terraform validate

# Show current state
terraform show

# List resources
terraform state list

# Import existing resource
terraform import aws_vpc.main vpc-12345678

# Refresh state
terraform refresh

# Show outputs
terraform output

# Target specific resource
terraform apply -target=aws_vpc.main
```

## Troubleshooting

### State Lock Issues

If state is locked:
```bash
# Force unlock (use with caution!)
terraform force-unlock <LOCK_ID>
```

### Provider Authentication

```bash
# Verify AWS credentials
aws sts get-caller-identity

# Check Terraform version
terraform version
```

### Debugging

Enable detailed logs:
```bash
export TF_LOG=DEBUG
terraform apply
```

## Examples

See the repository root for example deployments:
- Development environment
- Production environment  
- Multi-region setup

## Additional Resources

- [Terraform AWS Provider Documentation](https://registry.terraform.io/providers/hashicorp/aws/latest/docs)
- [Terraform Best Practices](https://www.terraform.io/docs/cloud/guides/recommended-practices/index.html)
- [AWS Well-Architected Framework](https://aws.amazon.com/architecture/well-architected/)
