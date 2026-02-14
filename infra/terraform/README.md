# Terraform Infrastructure

Infrastructure as Code using Terraform for AWS deployment.

## Features

- VPC with public subnets across multiple availability zones
- ECR repository for Docker images
- Automated image lifecycle management
- Tagged resources for cost tracking

## Usage

```bash
# Initialize Terraform
terraform init

# Plan changes
terraform plan

# Apply changes
terraform apply

# Destroy infrastructure
terraform destroy
```

## Configuration

Create a `terraform.tfvars` file to customize variables:

```hcl
aws_region         = "us-east-1"
environment        = "dev"
app_name           = "build-systems"
availability_zones = ["us-east-1a", "us-east-1b"]
```

## State Management

Configure S3 backend for remote state:

```hcl
terraform {
  backend "s3" {
    bucket = "your-terraform-state-bucket"
    key    = "build-systems/terraform.tfstate"
    region = "us-east-1"
  }
}
```

## Resources Created

- VPC with Internet Gateway
- 2 Public Subnets (multi-AZ)
- Route Tables
- ECR Repository with lifecycle policy
